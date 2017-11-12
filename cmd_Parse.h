#pragma once

#include "cmd_Commands.h"
#include "cmd_defs.h"

#include <optional>
#include <variant>

namespace tree
{
	class Node;
}

namespace cmd
{
	std::optional<std::pair<Command, Options>> ParseOptions(const std::string & line);

	std::variant<std::string, tree::Node *> ParsePath(const std::string & path, tree::Node * root);
}
