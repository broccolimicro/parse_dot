/*
 * assignment_list.h
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include "assignment.h"

#include <parse/parse.h>
#include <parse/syntax.h>

#ifndef parse_dot_assignment_list_h
#define parse_dot_assignment_list_h

namespace parse_dot
{

struct assignment_list : parse::syntax
{
	assignment_list();
	assignment_list(tokenizer &tokens, void *data = NULL);
	~assignment_list();

	vector<assignment> as;

	void parse(tokenizer &tokens, void *data = NULL);
	static bool is_next(tokenizer &tokens, int i = 1, void *data = NULL);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "") const;
	parse::syntax *clone() const;
};

}

#endif
