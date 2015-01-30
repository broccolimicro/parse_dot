/*
 * dot.h
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include <parse/parse.h>
#include <parse/syntax.h>
#include <parse/default/instance.h>

#ifndef dot_h
#define dot_h

namespace dot
{

struct node_id : parse::syntax
{
	node_id();
	node_id(configuration &config, tokenizer &tokens);
	node_id(string id);
	node_id(string id, string port);
	node_id(string id, string port, string compass);
	~node_id();

	string id;
	string port;
	string compass;

	void parse(configuration &config, tokenizer &tokens);
	static bool is_next(configuration &config, tokenizer &tokens, int i = 1);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "");
};

struct assignment : parse::syntax
{
	assignment();
	assignment(configuration &config, tokenizer &tokens);
	assignment(string first, string second);
	~assignment();

	string first;
	string second;

	void parse(configuration &config, tokenizer &tokens);
	static bool is_next(configuration &config, tokenizer &tokens, int i = 1);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "");
};

struct assignment_list : parse::syntax
{
	assignment_list();
	assignment_list(configuration &config, tokenizer &tokens);
	~assignment_list();

	vector<assignment> as;

	void parse(configuration &config, tokenizer &tokens);
	static bool is_next(configuration &config, tokenizer &tokens, int i = 1);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "");
};

struct attribute_list : parse::syntax
{
	attribute_list();
	attribute_list(configuration &config, tokenizer &tokens);
	~attribute_list();

	vector<assignment_list> attributes;

	void parse(configuration &config, tokenizer &tokens);
	static bool is_next(configuration &config, tokenizer &tokens, int i = 1);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "");
};

struct statement : parse::syntax
{
	statement();
	statement(configuration &config, tokenizer &tokens);
	~statement();

	string statement_type;
	string attribute_type;
	vector<parse::syntax*> nodes;
	attribute_list attributes;

	void parse(configuration &config, tokenizer &tokens);
	static bool is_next(configuration &config, tokenizer &tokens, int i = 1);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "");
};

struct graph : parse::syntax
{
	graph();
	graph(configuration &config, tokenizer &tokens);
	~graph();

	bool strict;
	string type;
	string id;
	vector<statement> statements;

	void parse(configuration &config, tokenizer &tokens);
	static bool is_next(configuration &config, tokenizer &tokens, int i = 1);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "");
};

struct cluster : parse::syntax
{
	cluster();
	cluster(configuration &config, tokenizer &tokens);
	~cluster();

	vector<graph> graphs;

	void parse(configuration &config, tokenizer &tokens);
	static bool is_next(configuration &config, tokenizer &tokens, int i = 1);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "");
};
}

#endif
