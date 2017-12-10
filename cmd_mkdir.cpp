#include "headers.h"
#include "cmd_Handlers.h"
#include "cmd_Parse.h"
#include "tree_Node.h"
#include <iostream>
#include <fstream>
#include <direct.h>

#ifdef _DEBUG
#define new DBG_NEW
#endif

using namespace cmd;
using namespace tree;

Handler cmd::Mkdir(const Options & options)
{
	return[path = options.path](Node * node, std::ostream & out)
	{
		std::ofstream outfile(path);

		outfile.close();

		return true;
	};
}