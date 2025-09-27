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
#include <parse/default/white_space.h>

namespace parse_dot
{
assignment::assignment()
{
	debug_name = "dot_assignment";
}

assignment::assignment(tokenizer &tokens, void *data)
{
	debug_name = "dot_assignment";
	parse(tokens, data);
}

assignment::assignment(string first, string second)
{
	debug_name = "dot_assignment";
	this->first = first;
	this->second = second;
	valid = true;
}

assignment::~assignment()
{
}

void assignment::parse(tokenizer &tokens, void *data)
{
	tokens.syntax_start(this);

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

	if (tokens.decrement(__FILE__, __LINE__, data))
		first = tokens.next();

	if (tokens.decrement(__FILE__, __LINE__, data))
		tokens.next();

	if (tokens.decrement(__FILE__, __LINE__, data))
		second = tokens.next();

	if ((int)first.size() >= 2 && first[0] == '\"' && first[first.size()-1] == '\"')
		first = first.substr(1, first.size()-2);

	if ((int)second.size() >= 2 && second[0] == '\"' && second[second.size()-1] == '\"')
		second = second.substr(1, second.size()-2);

	tokens.syntax_end(this);
}

bool assignment::is_next(tokenizer &tokens, int i, void *data)
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
		tokens.register_token<parse::white_space>(false);
	}
}

string assignment::to_string(string tab) const
{
	bool first_text = first.size() == 0;
	bool second_text = second.size() == 0;

	bool letter = false;
	bool number = false;
	bool symbol = false;
	for (int i = 0; i < (int)first.size(); i++)
	{
		if ((first[i] >= 'a' && first[i] <= 'z') || (first[i] >= 'A' && first[i] <= 'Z'))
			letter = true;
		else if (first[i] >= '0' && first[i] <= '9')
			number = true;
		else
			symbol = true;
	}

	if ((letter && number) || symbol)
		first_text = true;

	letter = false;
	number = false;
	symbol = false;
	for (int i = 0; i < (int)second.size(); i++)
	{
		if ((second[i] >= 'a' && second[i] <= 'z') || (second[i] >= 'A' && second[i] <= 'Z'))
			letter = true;
		else if (second[i] >= '0' && second[i] <= '9')
			number = true;
		else
			symbol = true;
	}

	if ((letter && number) || symbol)
		second_text = true;

	string result;
	if (first_text)
		result += "\"" + first + "\"";
	else
		result += first;

	result += "=";

	if (second_text)
		result += "\"" + second + "\"";
	else
		result += second;

	return result;
}

parse::syntax *assignment::clone() const
{
	return new assignment(*this);
}

}
