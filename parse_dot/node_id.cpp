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

namespace parse_dot
{
node_id::node_id()
{
	debug_name = "node_id";
}

node_id::node_id(configuration &config, tokenizer &tokens)
{
	debug_name = "node_id";
	parse(config, tokens);
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

void node_id::parse(configuration &config, tokenizer &tokens)
{
	valid = true;

	// Parse the ID
	tokens.increment(true);
	tokens.expect<parse::instance>();
	tokens.expect<parse::text>();
	tokens.expect<parse::number>();
	if (tokens.decrement(config, __FILE__, __LINE__))
	{
		id = tokens.next();

		// Parse the Port
		tokens.increment(false);
		tokens.expect(":");

		if (tokens.decrement(config, __FILE__, __LINE__))
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
			if (tokens.decrement(config, __FILE__, __LINE__))
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

					if (tokens.decrement(config, __FILE__, __LINE__))
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
						if (tokens.decrement(config, __FILE__, __LINE__))
							compass = tokens.next();
					}
				}
			}
		}
	}
}

bool node_id::is_next(configuration &config, tokenizer &tokens, int i)
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

}
