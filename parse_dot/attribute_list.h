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
	attribute_list(tokenizer &tokens, void *data = NULL);
	~attribute_list();

	vector<assignment_list> attributes;

	void parse(tokenizer &tokens, void *data = NULL);
	static bool is_next(tokenizer &tokens, int i = 1, void *data = NULL);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "") const;
	parse::syntax *clone() const;
};

}

#endif
