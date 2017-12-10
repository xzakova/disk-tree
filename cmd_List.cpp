#include "headers.h"
#include "cmd_Handlers.h"
#include "tree_Node.h"
#include "cmd_Parse.h"

#ifdef _DEBUG
#define new DBG_NEW
#endif

using namespace cmd;
using namespace tree;

Handler cmd::List(const Options & options)
{
	return [bFollow = options.bFollow, bRecursive = options.bRecursive, path = options.path](Node * node, std::ostream & out)
	{
		auto root = ParsePath(path, node);

		if (std::holds_alternative<std::string>(root))
			out << std::get<std::string>(root) << std::endl;

		if (std::holds_alternative<Node*>(root))
			std::get<Node*>(root)->List(bFollow, bRecursive, "", out);
			
		return true;
	};
}
