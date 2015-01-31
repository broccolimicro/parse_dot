/*
 * assignment_list.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include "assignment_list.h"
#include <parse/default/symbol.h>

namespace dot_lang
{

assignment_list::assignment_list()
{
	debug_name = "assignment_list";
}

assignment_list::assignment_list(configuration &config, tokenizer &tokens)
{
	debug_name = "assignment_list";
	parse(config, tokens);
}

assignment_list::~assignment_list()
{
}

void assignment_list::parse(configuration &config, tokenizer &tokens)
{
	valid = true;

	tokens.increment(true);
	tokens.expect("]");

	tokens.increment(false);
	tokens.expect<assignment>();

	tokens.increment(true);
	tokens.expect("[");

	if (tokens.decrement(config, __FILE__, __LINE__))
		tokens.next();

	while (tokens.decrement(config, __FILE__, __LINE__))
	{
		as.push_back(assignment(config, tokens));

		tokens.increment(false);
		tokens.expect<assignment>();

		tokens.increment(false);
		tokens.expect(";");
		tokens.expect(",");

		if (tokens.decrement(config, __FILE__, __LINE__))
			tokens.next();
	}

	if (tokens.decrement(config, __FILE__, __LINE__))
		tokens.next();
}

bool assignment_list::is_next(configuration &config, tokenizer &tokens, int i)
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

string assignment_list::to_string(string tab)
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
