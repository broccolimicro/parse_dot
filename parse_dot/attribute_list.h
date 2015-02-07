/*
 * attribute_list.h
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include "assignment_list.h"

#include <parse/parse.h>
#include <parse/syntax.h>

#ifndef parse_dot_attribute_list_h
#define parse_dot_attribute_list_h

namespace parse_dot
{

struct attribute_list : parse::syntax
{
	attribute_list();
	attribute_list(configuration &config, tokenizer &tokens);
	~attribute_list();

	vector<assignment_list> attributes;

	void parse(configuration &config, tokenizer &tokens);
	static bool is_next(configuration &config, tokenizer &tokens, int i = 1);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "") const;
};

}

#endif
