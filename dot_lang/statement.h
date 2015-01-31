/*
 * statement.h
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include "attribute_list.h"

#include <parse/parse.h>
#include <parse/syntax.h>

#ifndef dot_lang_statement_h
#define dot_lang_statement_h

namespace dot_lang
{

struct statement : parse::syntax
{
	statement();
	statement(configuration &config, tokenizer &tokens);
	~statement();

	string statement_type;
	string attribute_type;
	vector<parse::syntax*> nodes;
	attribute_list attributes;

	void parse(configuration &config, tokenizer &tokens);
	static bool is_next(configuration &config, tokenizer &tokens, int i = 1);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "");
};

}

#endif
