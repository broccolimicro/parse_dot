/*
 * assignment_list.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include "assignment_list.h"
#include <parse/default/symbol.h>

namespace parse_dot
{

assignment_list::assignment_list()
{
	debug_name = "assignment_list";
}

assignment_list::assignment_list(tokenizer &tokens, void *data)
{
	debug_name = "assignment_list";
	parse(tokens, data);
}

assignment_list::~assignment_list()
{
}

void assignment_list::parse(tokenizer &tokens, void *data)
{
	tokens.syntax_start(this);

	tokens.increment(true);
	tokens.expect("]");

	tokens.increment(false);
	tokens.expect<assignment>();

	tokens.increment(true);
	tokens.expect("[");

	if (tokens.decrement(__FILE__, __LINE__, data))
		tokens.next();

	while (tokens.decrement(__FILE__, __LINE__, data))
	{
		as.push_back(assignment(tokens, data));

		tokens.increment(false);
		tokens.expect<assignment>();

		tokens.increment(false);
		tokens.expect(";");
		tokens.expect(",");

		if (tokens.decrement(__FILE__, __LINE__, data))
			tokens.next();
	}

	if (tokens.decrement(__FILE__, __LINE__, data))
		tokens.next();

	tokens.syntax_end(this);
}

bool assignment_list::is_next(tokenizer &tokens, int i, void *data)
{
	return tokens.is_next("[", i);
}

void assignment_list::register_syntax(tokenizer &tokens)
{
	if (!tokens.syntax_registered<assignment_list>())
	{
		tokens.register_syntax<assignment_list>();
		assignment::register_syntax(tokens);
		tokens.register_token<parse::symbol>();
	}
}

string assignment_list::to_string(string tab) const
{
	string result = "";
	if (as.size() > 0)
	{
		result += "[";
		for (size_t i = 0; i < as.size(); i++)
		{
			if (i != 0)
				result += " ";
			result += as[i].to_string(tab);
		}
		result += "]";
	}

	return result;
}

}
