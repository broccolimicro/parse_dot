/*
 * assignment.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include "assignment.h"
#include <parse/default/instance.h>
#include <parse/default/text.h>
#include <parse/default/number.h>
#include <parse/default/symbol.h>

namespace parse_dot
{
assignment::assignment()
{
	debug_name = "assignment";
}

assignment::assignment(configuration &config, tokenizer &tokens)
{
	debug_name = "assignment";
	parse(config, tokens);
}

assignment::assignment(string first, string second)
{
	debug_name = "assignment";
	this->first = first;
	this->second = second;
	valid = true;
}

assignment::~assignment()
{
}

void assignment::parse(configuration &config, tokenizer &tokens)
{
	valid = true;

	tokens.increment(true);
	tokens.expect<parse::instance>();
	tokens.expect<parse::number>();
	tokens.expect<parse::text>();

	tokens.increment(true);
	tokens.expect("=");

	tokens.increment(true);
	tokens.expect<parse::instance>();
	tokens.expect<parse::number>();
	tokens.expect<parse::text>();

	if (tokens.decrement(config, __FILE__, __LINE__))
		first = tokens.next();

	if (tokens.decrement(config, __FILE__, __LINE__))
		tokens.next();

	if (tokens.decrement(config, __FILE__, __LINE__))
		second = tokens.next();
}

bool assignment::is_next(configuration &config, tokenizer &tokens, int i)
{
	return (tokens.is_next<parse::instance>(i) ||
			tokens.is_next<parse::number>(i) ||
			tokens.is_next<parse::text>(i));
}

void assignment::register_syntax(tokenizer &tokens)
{
	if (!tokens.syntax_registered<assignment>())
	{
		tokens.register_syntax<assignment>();
		tokens.register_token<parse::instance>();
		tokens.register_token<parse::number>();
		tokens.register_token<parse::text>();
		tokens.register_token<parse::symbol>();
	}
}

string assignment::to_string(string tab) const
{
	string result;
	if (first != "")
		result += first;
	else
		result += "null";

	result += "=";

	if (second != "")
		result += second;
	else
		result = "null";

	return result;
}

}
