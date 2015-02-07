/*
 * node_id.h
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include <parse/parse.h>
#include <parse/syntax.h>

#ifndef parse_dot_node_id_h
#define parse_dot_node_id_h

namespace parse_dot
{

struct node_id : parse::syntax
{
	node_id();
	node_id(configuration &config, tokenizer &tokens);
	node_id(string id);
	node_id(string id, string port);
	node_id(string id, string port, string compass);
	~node_id();

	string id;
	string port;
	string compass;

	void parse(configuration &config, tokenizer &tokens);
	static bool is_next(configuration &config, tokenizer &tokens, int i = 1);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "") const;
};

}

#endif
