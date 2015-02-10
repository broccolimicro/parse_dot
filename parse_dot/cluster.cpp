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

cluster::cluster(tokenizer &tokens, void *data)
{
	debug_name = "cluster";
	parse(tokens, data);
}

cluster::~cluster()
{

}

void cluster::parse(tokenizer &tokens, void *data)
{
	tokens.syntax_start(this);

	tokens.increment(false);
	tokens.expect<graph>();

	while (tokens.decrement(__FILE__, __LINE__, data))
	{
		graphs.push_back(graph(tokens, data));

		tokens.increment(false);
		tokens.expect<graph>();
	}

	tokens.syntax_end(this);
}

bool cluster::is_next(tokenizer &tokens, int i, void *data)
{
	return graph::is_next(tokens, i, data);
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
