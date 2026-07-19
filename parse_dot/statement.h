/*
 * statement.h
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include "attribute_list.h"

#include <parse/parse.h>
#include <parse/syntax.h>

#ifndef parse_dot_statement_h
#define parse_dot_statement_h

namespace parse_dot
{

struct statement : parse::syntax
{
	statement();
	statement(tokenizer &tokens, std::any data=std::any());
	~statement();

	string statement_type;
	string attribute_type;
	vector<parse::syntax*> nodes;
	attribute_list attributes;

	void parse(tokenizer &tokens, std::any data=std::any());
	static bool is_next(tokenizer &tokens, int i = 1, std::any data=std::any());
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "") const;
	parse::syntax *clone() const;
};

}

#endif
