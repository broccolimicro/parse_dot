/*
 * node_id.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include "node_id.h"
#include <parse/default/instance.h>
#include <parse/default/text.h>
#include <parse/default/number.h>
#include <parse/default/symbol.h>
#include <parse/default/white_space.h>

namespace parse_dot
{
node_id::node_id()
{
	debug_name = "node_id";
}

node_id::node_id(tokenizer &tokens, void *data)
{
	debug_name = "node_id";
	parse(tokens, data);
}

node_id::node_id(string id)
{
	debug_name = "node_id";
	this->id = id;
}

node_id::node_id(string id, string port)
{
	debug_name = "node_id";
	this->id = id;
	this->port = port;
}

node_id::node_id(string id, string port, string compass)
{
	debug_name = "node_id";
	this->id = id;
	this->port = port;
	this->compass = compass;
}

node_id::~node_id()
{
}

void node_id::parse(tokenizer &tokens, void *data)
{
	tokens.syntax_start(this);

	// Parse the ID
	tokens.increment(true);
	tokens.expect<parse::instance>();
	tokens.expect<parse::text>();
	tokens.expect<parse::number>();
	if (tokens.decrement(__FILE__, __LINE__, data))
	{
		id = tokens.next();

		// Parse the Port
		tokens.increment(false);
		tokens.expect(":");

		if (tokens.decrement(__FILE__, __LINE__, data))
		{
			tokens.next();

			tokens.increment(true);
			tokens.expect<parse::instance>();
			tokens.expect<parse::text>();
			tokens.expect<parse::number>();
			tokens.expect("n");
			tokens.expect("ne");
			tokens.expect("e");
			tokens.expect("se");
			tokens.expect("s");
			tokens.expect("sw");
			tokens.expect("w");
			tokens.expect("nw");
			tokens.expect("c");
			tokens.expect("_");
			if (tokens.decrement(__FILE__, __LINE__, data))
			{
				if (tokens.found("n") || tokens.found("ne") || tokens.found("e") || tokens.found("se") || tokens.found("s") ||
					tokens.found("sw") || tokens.found("w") || tokens.found("nw") || tokens.found("c") || tokens.found("_"))
					compass = tokens.next();
				else
				{
					port = tokens.next();

					// Parse the Compass Points
					tokens.increment(false);
					tokens.expect(":");

					if (tokens.decrement(__FILE__, __LINE__, data))
					{
						tokens.next();
						tokens.increment(true);
						tokens.expect("n");
						tokens.expect("ne");
						tokens.expect("e");
						tokens.expect("se");
						tokens.expect("s");
						tokens.expect("sw");
						tokens.expect("w");
						tokens.expect("nw");
						tokens.expect("c");
						tokens.expect("_");
						if (tokens.decrement(__FILE__, __LINE__, data))
							compass = tokens.next();
					}
				}
			}
		}
	}

	tokens.syntax_end(this);
}

bool node_id::is_next(tokenizer &tokens, int i, void *data)
{
	return (tokens.is_next<parse::instance>(i) ||
			tokens.is_next<parse::number>(i) ||
			tokens.is_next<parse::text>(i));
}

void node_id::register_syntax(tokenizer &tokens)
{
	if (!tokens.syntax_registered<node_id>())
	{
		tokens.register_syntax<node_id>();
		tokens.register_token<parse::instance>();
		tokens.register_token<parse::number>();
		tokens.register_token<parse::text>();
		tokens.register_token<parse::symbol>();
		tokens.register_token<parse::white_space>(false);
	}
}

string node_id::to_string(string tab) const
{
	string result = "";
	if (id != "")
		result += id;
	else
		result += "null";

	if (port != "")
		result += " : " + port;

	if (compass != "")
		result += " : " + compass;

	return result;
}

parse::syntax *node_id::clone() const
{
	return new node_id(*this);
}

}
