#pragma once

#include "tree_Node.h"

#include <vector>
#include <regex>

namespace tree
{
	class Folder : public Node
	{
	public:
		Folder(const std::string & name) : Node(name) {}
		virtual ~Folder() {}

		tree::Size Size(bool bFollow, bool bRecursive) const override;
		void List(bool bFollow, bool bRecursive, const std::string & offset, std::ostream & out) const override;

		void Insert(Node * node);
		void Remove(const Node * node);
		const std::vector<Node*> & Content() const { return _content; }

		Node * Find(const std::string & path) const;
		Node * Find(std::sregex_token_iterator iter) const;

		static Folder * Parse(rapidjson::Value & json);

	private:
		std::vector<Node*> _content;
	};
}
