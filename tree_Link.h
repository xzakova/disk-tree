#pragma once
#include "tree_Node.h"
#include <memory>

namespace tree
{
	class Link : public Node
	{
	public:
		Link(const std::string & name, const std::string & path) : Node(name), _path(path)
		{
		}
		virtual ~Link() {}

		tree::Size Size(bool bFollow, bool bRecursive) const override;
		void List(bool bFollow, bool bRecursive, const std::string & offset, std::ostream & out) const override;

		void Set(Node * link) { _link = link; }
		Node * Get() const { return _link; }

		const std::string & Path() const { return _path; }

		static std::unique_ptr<Link> Parse(rapidjson::Value & json);

	private:
		Node * _link { nullptr };
		const std::string _path;
	};
}
