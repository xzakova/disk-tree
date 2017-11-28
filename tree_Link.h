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

		void Set(std::shared_ptr<Node> link) { _link = link; }
		std::shared_ptr<Node> Get() const { return _link.lock(); }

		const std::string & Path() const { return _path; }

		static std::shared_ptr<Link> Parse(rapidjson::Value & json);

	private:
		std::weak_ptr<Node> _link;
		const std::string _path;
	};
}
