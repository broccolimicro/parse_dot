/*
 * attribute_list.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include "attribute_list.h"
#include <parse/default/symbol.h>

namespace dot_lang
{

attribute_list::attribute_list()
{
	debug_name = "attribute_list";
}

attribute_list::attribute_list(configuration &config, tokenizer &tokens)
{
	debug_name = "attribute_list";
	parse(config, tokens);
}

attribute_list::~attribute_list()
{
}

void attribute_list::parse(configuration &config, tokenizer &tokens)
{
	tokens.increment(false);
	tokens.expect<assignment_list>();

	while (tokens.decrement(config, __FILE__, __LINE__))
	{
		attributes.push_back(assignment_list(config, tokens));

		tokens.increment(false);
		tokens.expect<assignment_list>();
	}
}

bool attribute_list::is_next(configuration &config, tokenizer &tokens, int i)
{
	return assignment_list::is_next(config, tokens, i);
}

void attribute_list::register_syntax(tokenizer &tokens)
{
	if (!tokens.syntax_registered<attribute_list>())
	{
		tokens.register_syntax<attribute_list>();
		assignment_list::register_syntax(tokens);
		tokens.register_token<parse::symbol>();
	}
}

string attribute_list::to_string(string tab)
{
	string result;
	for (size_t i = 0; i < attributes.size(); i++)
		result += attributes[i].to_string(tab);
	return result;
}

}
