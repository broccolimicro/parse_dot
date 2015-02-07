/*
 * statement.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include "statement.h"
#include "node_id.h"
#include "graph.h"

#include <parse/default/instance.h>
#include <parse/default/symbol.h>

namespace parse_dot
{
statement::statement()
{
	debug_name = "statement";
}

statement::statement(configuration &config, tokenizer &tokens)
{
	debug_name = "statement";
	parse(config, tokens);
}

statement::~statement()
{

}

void statement::parse(configuration &config, tokenizer &tokens)
{
	valid = true;

	statement_type = "node";
	tokens.increment(true);
	tokens.expect("graph");
	tokens.expect("node");
	tokens.expect("edge");
	tokens.expect<node_id>();
	tokens.expect("subgraph");

	if (tokens.decrement(config, __FILE__, __LINE__))
	{
		if (tokens.found("subgraph"))
			nodes.push_back(new graph(config, tokens));
		else if (tokens.found<node_id>())
			nodes.push_back(new node_id(config, tokens));
		else
		{
			statement_type = "attribute";
			attribute_type = tokens.next();
		}
	}

	if (statement_type != "attribute")
	{
		tokens.increment(false);
		tokens.expect("->");
		tokens.expect("--");
		while (tokens.decrement(config, __FILE__, __LINE__))
		{
			statement_type = "edge";
			tokens.next();

			tokens.increment(false);
			tokens.expect("->");
			tokens.expect("--");

			tokens.increment(true);
			tokens.expect<node_id>();
			tokens.expect("subgraph");

			if (tokens.decrement(config, __FILE__, __LINE__))
			{
				if (tokens.found("subgraph"))
					nodes.push_back(new graph(config, tokens));
				else if (tokens.found<node_id>())
					nodes.push_back(new node_id(config, tokens));
			}
		}
	}

	tokens.increment(statement_type == "attribute");
	tokens.expect<attribute_list>();

	if (tokens.decrement(config, __FILE__, __LINE__))
		attributes.parse(config, tokens);
}

bool statement::is_next(configuration &config, tokenizer &tokens, int i)
{
	return (node_id::is_next(config, tokens, i) ||
			tokens.is_next("subgraph") ||
			tokens.is_next("graph") ||
			tokens.is_next("node") ||
			tokens.is_next("edge"));
}

void statement::register_syntax(tokenizer &tokens)
{
	if (!tokens.syntax_registered<statement>())
	{
		tokens.register_syntax<statement>();
		node_id::register_syntax(tokens);
		attribute_list::register_syntax(tokens);
		graph::register_syntax(tokens);
		tokens.register_token<parse::instance>();
		tokens.register_token<parse::symbol>();
	}
}

string statement::to_string(string tab) const
{
	string result;
	if (statement_type != "attribute")
	{
		for (int i = 0; i < (int)nodes.size(); i++)
		{
			if (i != 0)
				result += "->";
			if (nodes[i] != NULL)
				result += nodes[i]->to_string(tab);
		}
	}
	else
		result += attribute_type + " ";

	result += attributes.to_string(tab);

	return result;
}

}
