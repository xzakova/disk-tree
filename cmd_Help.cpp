#include "headers.h"
#include "cmd_Handlers.h"

#ifdef _DEBUG
#define new DBG_NEW
#endif

using namespace cmd;
using namespace tree;

bool cmd::Help(tree::Node *, std::ostream & out)
{
	//todo: print command help
	out << "help..." << std::endl;

	return true;
}
