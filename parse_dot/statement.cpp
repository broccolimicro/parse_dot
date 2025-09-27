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
#include <parse/default/white_space.h>

namespace parse_dot
{
statement::statement()
{
	debug_name = "dot_statement";
}

statement::statement(tokenizer &tokens, void *data)
{
	debug_name = "dot_statement";
	parse(tokens, data);
}

statement::~statement()
{

}

void statement::parse(tokenizer &tokens, void *data)
{
	tokens.syntax_start(this);

	statement_type = "node";
	tokens.increment(true);
	tokens.expect("graph");
	tokens.expect("node");
	tokens.expect("edge");
	tokens.expect<node_id>();
	tokens.expect("subgraph");

	if (tokens.decrement(__FILE__, __LINE__, data))
	{
		if (tokens.found("subgraph"))
			nodes.push_back(new graph(tokens, data));
		else if (tokens.found<node_id>())
			nodes.push_back(new node_id(tokens, data));
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
		while (tokens.decrement(__FILE__, __LINE__, data))
		{
			statement_type = "edge";
			tokens.next();

			tokens.increment(false);
			tokens.expect("->");
			tokens.expect("--");

			tokens.increment(true);
			tokens.expect<node_id>();
			tokens.expect("subgraph");

			if (tokens.decrement(__FILE__, __LINE__, data))
			{
				if (tokens.found("subgraph"))
					nodes.push_back(new graph(tokens, data));
				else if (tokens.found<node_id>())
					nodes.push_back(new node_id(tokens, data));
			}
		}
	}

	tokens.increment(statement_type == "attribute");
	tokens.expect<attribute_list>();

	if (tokens.decrement(__FILE__, __LINE__, data))
		attributes.parse(tokens, data);

	tokens.syntax_end(this);
}

bool statement::is_next(tokenizer &tokens, int i, void *data)
{
	return (node_id::is_next(tokens, i, data) ||
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
		tokens.register_token<parse::white_space>(false);
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

parse::syntax *statement::clone() const
{
	return new statement(*this);
}

}
