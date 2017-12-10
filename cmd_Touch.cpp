#include "headers.h"
#include "cmd_Handlers.h"
#include "cmd_Parse.h"
#include "tree_Node.h"
#include <iostream>
#include <fstream>

#ifdef _DEBUG
#define new DBG_NEW
#endif

using namespace cmd;
using namespace tree;

Handler cmd::Touch(const Options & options)
{
	return[size = options.size, path = options.path](Node * node, std::ostream & out)
	{
		std::ofstream outfile(path);

		outfile << size;
		outfile.close();

		return true;
	};
}