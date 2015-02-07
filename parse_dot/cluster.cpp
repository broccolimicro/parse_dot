/*
 * cluster.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include "cluster.h"

namespace parse_dot
{

cluster::cluster()
{
	debug_name = "cluster";
}

cluster::cluster(configuration &config, tokenizer &tokens)
{
	debug_name = "cluster";
	parse(config, tokens);
}

cluster::~cluster()
{

}

void cluster::parse(configuration &config, tokenizer &tokens)
{
	valid = true;

	tokens.increment(false);
	tokens.expect<graph>();

	while (tokens.decrement(config, __FILE__, __LINE__))
	{
		graphs.push_back(graph(config, tokens));

		tokens.increment(false);
		tokens.expect<graph>();
	}
}

bool cluster::is_next(configuration &config, tokenizer &tokens, int i)
{
	return graph::is_next(config, tokens, i);
}

void cluster::register_syntax(tokenizer &tokens)
{
	if (!tokens.syntax_registered<cluster>())
	{
		tokens.register_syntax<cluster>();
		graph::register_syntax(tokens);
	}
}

string cluster::to_string(string tab) const
{
	string result = "";
	for (int i = 0; i < (int)graphs.size(); i++)
	{
		result += graphs[i].to_string(tab);
		result += tab;
	}
	return result;
}
}
