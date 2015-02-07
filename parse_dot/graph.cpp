/*
 * graph.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include "graph.h"
#include <parse/default/instance.h>
#include <parse/default/symbol.h>

namespace parse_dot
{

graph::graph()
{
	debug_name = "graph";
	strict = false;
}

graph::graph(configuration &config, tokenizer &tokens)
{
	debug_name = "graph";
	strict = false;
	parse(config, tokens);
}

graph::~graph()
{
}

void graph::parse(configuration &config, tokenizer &tokens)
{
	valid = true;

	tokens.increment(true);
	tokens.expect("}");

	tokens.increment(false);
	tokens.expect<statement>();

	tokens.increment(true);
	tokens.expect("{");

	tokens.increment(false);
	tokens.expect<parse::instance>();

	tokens.increment(true);
	tokens.expect("graph");
	tokens.expect("digraph");
	tokens.expect("subgraph");

	tokens.increment(false);
	tokens.expect("strict");

	if (tokens.decrement(config, __FILE__, __LINE__))
	{
		tokens.next();
		strict = true;
	}

	if (tokens.decrement(config, __FILE__, __LINE__))
		type = tokens.next();

	if (tokens.decrement(config, __FILE__, __LINE__))
		id = tokens.next();

	if (tokens.decrement(config, __FILE__, __LINE__))
		tokens.next();

	while (tokens.decrement(config, __FILE__, __LINE__))
	{
		statements.push_back(statement(config, tokens));

		tokens.increment(false);
		tokens.expect<statement>();

		tokens.increment(false);
		tokens.expect(";");

		if (tokens.decrement(config, __FILE__, __LINE__))
			tokens.next();
	}

	if (tokens.decrement(config, __FILE__, __LINE__))
		tokens.next();
}

bool graph::is_next(configuration &config, tokenizer &tokens, int i)
{
	return (tokens.is_next("strict") || tokens.is_next("graph") || tokens.is_next("digraph") || tokens.is_next("subgraph"));
}

void graph::register_syntax(tokenizer &tokens)
{
	if (!tokens.syntax_registered<graph>())
	{
		tokens.register_syntax<graph>();
		statement::register_syntax(tokens);
		tokens.register_token<parse::instance>();
		tokens.register_token<parse::symbol>();
	}
}

string graph::to_string(string tab) const
{
	string result = "";
	if (strict)
		result += "strict ";

	result += type + " " + id + "\n" + tab + "{" + "\n";
	for (int i = 0; i < (int)statements.size(); i++)
		result += tab + "\t" + statements[i].to_string(tab + "\t") + "\n";
	result += tab + "}\n";
	return result;
}

}
