/*
 * graph.h
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include "statement.h"

#include <parse/parse.h>
#include <parse/syntax.h>

#ifndef parse_dot_graph_h
#define parse_dot_graph_h

namespace parse_dot
{

struct graph : parse::syntax
{
	graph();
	graph(tokenizer &tokens, void *data = NULL);
	~graph();

	bool strict;
	string type;
	string id;
	vector<statement> statements;

	void parse(tokenizer &tokens, void *data = NULL);
	static bool is_next(tokenizer &tokens, int i = 1, void *data = NULL);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "") const;
};

}

#endif
