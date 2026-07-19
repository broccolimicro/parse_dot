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
	graph(tokenizer &tokens, std::any data=std::any());
	~graph();

	bool strict;
	string type;
	string id;
	vector<assignment> attributes;
	vector<statement> statements;

	void parse(tokenizer &tokens, std::any data=std::any());
	static bool is_next(tokenizer &tokens, int i = 1, std::any data=std::any());
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "") const;
	parse::syntax *clone() const;
};

}

#endif
