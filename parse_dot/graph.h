/*
 * graph.h
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include "statement.h"

#include <parse/parse.h>
#include <parse/syntax.h>

#ifndef dot_lang_graph_h
#define dot_lang_graph_h

namespace dot_lang
{

struct graph : parse::syntax
{
	graph();
	graph(configuration &config, tokenizer &tokens);
	~graph();

	bool strict;
	string type;
	string id;
	vector<statement> statements;

	void parse(configuration &config, tokenizer &tokens);
	static bool is_next(configuration &config, tokenizer &tokens, int i = 1);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "");
};

}

#endif
