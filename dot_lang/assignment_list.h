/*
 * assignment_list.h
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include "assignment.h"

#include <parse/parse.h>
#include <parse/syntax.h>

#ifndef assignment_list_h
#define assignment_list_h

namespace dot_lang
{

struct assignment_list : parse::syntax
{
	assignment_list();
	assignment_list(configuration &config, tokenizer &tokens);
	~assignment_list();

	vector<assignment> as;

	void parse(configuration &config, tokenizer &tokens);
	static bool is_next(configuration &config, tokenizer &tokens, int i = 1);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "");
};

}

#endif
