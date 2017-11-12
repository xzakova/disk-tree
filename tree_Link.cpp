#include "headers.h"
#include "tree_Link.h"

#ifdef _DEBUG
#define new DBG_NEW
#endif

using namespace tree;

tree::Size Link::Size(bool bFollow, bool bRecursive) const
{
	return bFollow && _link ? _link->Size(bFollow, bRecursive) : .0;
}

void Link::List(bool bFollow, bool bRecursive, const std::string & offset, std::ostream & out) const
{
	out << Name() << " -" << (_link ? "-" : "X") << "-> " << _path;
	if (_link && bFollow)
	{
		out << " // ";
		_link->List(bFollow, bRecursive, offset, out);
	}
	else
	{
		out << std::endl;
	}
}

Link * Link::Parse(rapidjson::Value & json)
{
	if (!json.HasMember("name") || !json.HasMember("link"))
		return nullptr;

	return new Link(json["name"].GetString(), json["link"].GetString());
}
