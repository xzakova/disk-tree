#include "headers.h"
#include "tree_Node.h"
#include "tree_File.h"
#include "tree_Folder.h"
#include "tree_Link.h"

#include <memory>

#ifdef _DEBUG
#define new DBG_NEW
#endif

using namespace tree;

std::shared_ptr <Node> Node::Parse(rapidjson::Value & json)
{
	if (json.HasMember("size"))
	{
		return File::Parse(json);
	}
	else if (json.HasMember("link"))
	{
		return Link::Parse(json);
	}
	else
	{
		return Folder::Parse(json);
	}
}
