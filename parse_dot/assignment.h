/*
 * assignment.h
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include <parse/parse.h>
#include <parse/syntax.h>

#ifndef parse_dot_assignment_h
#define parse_dot_assignment_h

namespace parse_dot
{

struct assignment : parse::syntax
{
	assignment();
	assignment(tokenizer &tokens, void *data = NULL);
	assignment(string first, string second);
	~assignment();

	string first;
	string second;

	void parse(tokenizer &tokens, void *data = NULL);
	static bool is_next(tokenizer &tokens, int i = 1, void *data = NULL);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "") const;
	parse::syntax *clone() const;
};

}

#endif
