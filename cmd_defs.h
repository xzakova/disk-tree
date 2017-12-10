#pragma once

#include <string>
#include <ostream>
#include <functional>

namespace tree
{
	class Node;
}

namespace cmd
{
	using Handler = std::function<bool(tree::Node*, std::ostream&)>;

	struct Options
	{
		bool bFollow;
		bool bRecursive;
		std::string path;
		std::string size;
		std::string name;
	};
}
