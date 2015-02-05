/*
 * attribute_list.h
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include "assignment_list.h"

#include <parse/parse.h>
#include <parse/syntax.h>

#ifndef dot_lang_attribute_list_h
#define dot_lang_attribute_list_h

namespace dot_lang
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

	string to_string(string tab = "");
};

}

#endif
