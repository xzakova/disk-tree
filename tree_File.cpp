#include "headers.h"
#include "tree_File.h"

#include <ostream>
#include <memory>

#ifdef _DEBUG
#define new DBG_NEW
#endif

using namespace tree;

void tree::File::List(bool /*bFollow*/, bool /*bRecursive*/, const std::string & /*offset*/, std::ostream & out) const
{
	out << Name() << " [" << _size.toString() << "]" << std::endl;
}

std::unique_ptr<File> tree::File::Parse(rapidjson::Value & json)
{
	if (!json.HasMember("name"))
		return nullptr;

	tree::Size size { json["size"].GetString() };
	if (size < tree::Size())
		return nullptr;

	std::unique_ptr<File> file(new File(json["name"].GetString(), size));
	return file;

	//return new File(json["name"].GetString(), size);
}
