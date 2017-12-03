#pragma once

#include "tree_Folder.h"
#include <memory>

namespace tree
{
	std::shared_ptr<tree::Folder> ParseDisk(rapidjson::Value & json);
}
