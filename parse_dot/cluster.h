/*
 * cluster.h
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include "graph.h"

#include <parse/parse.h>
#include <parse/syntax.h>

#ifndef parse_dot_cluster_h
#define parse_dot_cluster_h

namespace parse_dot
{
struct cluster : parse::syntax
{
	cluster();
	cluster(tokenizer &tokens, void *data = NULL);
	~cluster();

	vector<graph> graphs;

	void parse(tokenizer &tokens, void *data = NULL);
	static bool is_next(tokenizer &tokens, int i = 1, void *data = NULL);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "") const;
	parse::syntax *clone() const;
};
}

#endif
