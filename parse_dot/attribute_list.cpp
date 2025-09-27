/*
 * attribute_list.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include "attribute_list.h"
#include <parse/default/symbol.h>
#include <parse/default/white_space.h>

namespace parse_dot
{

attribute_list::attribute_list()
{
	debug_name = "dot_attribute_list";
}

attribute_list::attribute_list(tokenizer &tokens, void *data)
{
	debug_name = "dot_attribute_list";
	parse(tokens, data);
}

attribute_list::~attribute_list()
{
}

void attribute_list::parse(tokenizer &tokens, void *data)
{
	tokens.syntax_start(this);

	tokens.increment(false);
	tokens.expect<assignment_list>();

	while (tokens.decrement(__FILE__, __LINE__, data))
	{
		attributes.push_back(assignment_list(tokens, data));

		tokens.increment(false);
		tokens.expect<assignment_list>();
	}

	tokens.syntax_end(this);
}

bool attribute_list::is_next(tokenizer &tokens, int i, void *data)
{
	return assignment_list::is_next(tokens, i, data);
}

void attribute_list::register_syntax(tokenizer &tokens)
{
	if (!tokens.syntax_registered<attribute_list>())
	{
		tokens.register_syntax<attribute_list>();
		assignment_list::register_syntax(tokens);
		tokens.register_token<parse::symbol>();
		tokens.register_token<parse::white_space>(false);
	}
}

string attribute_list::to_string(string tab) const
{
	string result;
	for (size_t i = 0; i < attributes.size(); i++)
		result += attributes[i].to_string(tab);
	return result;
}

parse::syntax *attribute_list::clone() const
{
	return new attribute_list(*this);
}

}
