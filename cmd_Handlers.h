#pragma once

#include "cmd_defs.h"

#include <ostream>

namespace tree
{
	class Node;
}

namespace cmd
{
	bool Help(tree::Node *, std::ostream & out);
	bool Quit(tree::Node *, std::ostream & out);

	Handler Size(const Options & options);
	Handler List(const Options & options);
}
