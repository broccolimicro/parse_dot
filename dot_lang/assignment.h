/*
 * assignment.h
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include <parse/parse.h>
#include <parse/syntax.h>

#ifndef assignment_h
#define assignment_h

namespace dot_lang
{

struct assignment : parse::syntax
{
	assignment();
	assignment(configuration &config, tokenizer &tokens);
	assignment(string first, string second);
	~assignment();

	string first;
	string second;

	void parse(configuration &config, tokenizer &tokens);
	static bool is_next(configuration &config, tokenizer &tokens, int i = 1);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "");
};

}

#endif
