/*
 * dot.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include "dot.h"
#include <parse/default/instance.h>
#include <parse/default/text.h>
#include <parse/default/number.h>
#include <parse/default/symbol.h>

namespace dot
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

string node_id::to_string(string tab)
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

string assignment::to_string(string tab)
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

statement::statement()
{
	debug_name = "statement";
}

statement::statement(configuration &config, tokenizer &tokens)
{
	debug_name = "statement";
	parse(config, tokens);
}

statement::~statement()
{

}

void statement::parse(configuration &config, tokenizer &tokens)
{
	valid = true;

	statement_type = "node";
	tokens.increment(true);
	tokens.expect("graph");
	tokens.expect("node");
	tokens.expect("edge");
	tokens.expect<node_id>();
	tokens.expect("subgraph");

	if (tokens.decrement(config, __FILE__, __LINE__))
	{
		if (tokens.found("subgraph"))
			nodes.push_back(new graph(config, tokens));
		else if (tokens.found<node_id>())
			nodes.push_back(new node_id(config, tokens));
		else
		{
			statement_type = "attribute";
			attribute_type = tokens.next();
		}
	}

	if (statement_type != "attribute")
	{
		tokens.increment(false);
		tokens.expect("->");
		tokens.expect("--");
		while (tokens.decrement(config, __FILE__, __LINE__))
		{
			statement_type = "edge";
			tokens.next();

			tokens.increment(false);
			tokens.expect("->");
			tokens.expect("--");

			tokens.increment(true);
			tokens.expect<node_id>();
			tokens.expect("subgraph");

			if (tokens.decrement(config, __FILE__, __LINE__))
			{
				if (tokens.found("subgraph"))
					nodes.push_back(new graph(config, tokens));
				else if (tokens.found<node_id>())
					nodes.push_back(new node_id(config, tokens));
			}
		}
	}

	tokens.increment(statement_type == "attribute");
	tokens.expect<attribute_list>();

	if (tokens.decrement(config, __FILE__, __LINE__))
		attributes.parse(config, tokens);
}

bool statement::is_next(configuration &config, tokenizer &tokens, int i)
{
	return (node_id::is_next(config, tokens, i) ||
			tokens.is_next("subgraph") ||
			tokens.is_next("graph") ||
			tokens.is_next("node") ||
			tokens.is_next("edge"));
}

void statement::register_syntax(tokenizer &tokens)
{
	if (!tokens.syntax_registered<statement>())
	{
		tokens.register_syntax<statement>();
		node_id::register_syntax(tokens);
		attribute_list::register_syntax(tokens);
		graph::register_syntax(tokens);
		tokens.register_token<parse::instance>();
		tokens.register_token<parse::symbol>();
	}
}

string statement::to_string(string tab)
{
	string result;
	if (statement_type != "attribute")
	{
		for (int i = 0; i < (int)nodes.size(); i++)
		{
			if (i != 0)
				result += "->";
			if (nodes[i] != NULL)
				result += nodes[i]->to_string(tab);
		}
	}
	else
		result += attribute_type + " ";

	result += attributes.to_string(tab);

	return result;
}

graph::graph()
{
	debug_name = "graph";
	strict = false;
}

graph::graph(configuration &config, tokenizer &tokens)
{
	debug_name = "graph";
	strict = false;
	parse(config, tokens);
}

graph::~graph()
{
}

void graph::parse(configuration &config, tokenizer &tokens)
{
	valid = true;

	tokens.increment(true);
	tokens.expect("}");

	tokens.increment(false);
	tokens.expect<statement>();

	tokens.increment(true);
	tokens.expect("{");

	tokens.increment(false);
	tokens.expect<parse::instance>();

	tokens.increment(true);
	tokens.expect("graph");
	tokens.expect("digraph");
	tokens.expect("subgraph");

	tokens.increment(false);
	tokens.expect("strict");

	if (tokens.decrement(config, __FILE__, __LINE__))
	{
		tokens.next();
		strict = true;
	}

	if (tokens.decrement(config, __FILE__, __LINE__))
		type = tokens.next();

	if (tokens.decrement(config, __FILE__, __LINE__))
		id = tokens.next();

	if (tokens.decrement(config, __FILE__, __LINE__))
		tokens.next();

	while (tokens.decrement(config, __FILE__, __LINE__))
	{
		statements.push_back(statement(config, tokens));

		tokens.increment(false);
		tokens.expect<statement>();

		tokens.increment(false);
		tokens.expect(";");

		if (tokens.decrement(config, __FILE__, __LINE__))
			tokens.next();
	}

	if (tokens.decrement(config, __FILE__, __LINE__))
		tokens.next();
}

bool graph::is_next(configuration &config, tokenizer &tokens, int i)
{
	return (tokens.is_next("strict") || tokens.is_next("graph") || tokens.is_next("digraph") || tokens.is_next("subgraph"));
}

void graph::register_syntax(tokenizer &tokens)
{
	if (!tokens.syntax_registered<graph>())
	{
		tokens.register_syntax<graph>();
		statement::register_syntax(tokens);
		tokens.register_token<parse::instance>();
		tokens.register_token<parse::symbol>();
	}
}

string graph::to_string(string tab)
{
	string result = "";
	if (strict)
		result += "strict ";

	result += type + " " + id + "\n" + tab + "{" + "\n";
	for (int i = 0; i < (int)statements.size(); i++)
		result += tab + "\t" + statements[i].to_string(tab + "\t") + "\n";
	result += tab + "}\n";
	return result;
}

cluster::cluster()
{
	debug_name = "cluster";
}

cluster::cluster(configuration &config, tokenizer &tokens)
{
	debug_name = "cluster";
	parse(config, tokens);
}

cluster::~cluster()
{

}

void cluster::parse(configuration &config, tokenizer &tokens)
{
	valid = true;

	tokens.increment(false);
	tokens.expect<graph>();

	while (tokens.decrement(config, __FILE__, __LINE__))
	{
		graphs.push_back(graph(config, tokens));

		tokens.increment(false);
		tokens.expect<graph>();
	}
}

bool cluster::is_next(configuration &config, tokenizer &tokens, int i)
{
	return graph::is_next(config, tokens, i);
}

void cluster::register_syntax(tokenizer &tokens)
{
	if (!tokens.syntax_registered<cluster>())
	{
		tokens.register_syntax<cluster>();
		graph::register_syntax(tokens);
	}
}

string cluster::to_string(string tab)
{
	string result = "";
	for (int i = 0; i < (int)graphs.size(); i++)
	{
		result += graphs[i].to_string(tab);
		result += tab;
	}
	return result;
}
}
