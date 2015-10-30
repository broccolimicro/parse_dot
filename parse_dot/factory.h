/*
 * factory.h
 *
 *  Created on: Aug 16, 2015
 *      Author: nbingham
 */

#include "graph.h"

#ifndef factory_h
#define factory_h

namespace parse_dot
{
	parse::syntax *factory(tokenizer &tokens, void *data)
	{
		return new graph(tokens, data);
	};
}

#endif
