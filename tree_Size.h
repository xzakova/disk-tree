#pragma once

#include <string>

namespace tree
{
	class Size
	{
	public:
		Size() {}
		Size(double size) : _size(size) {}
		Size(const std::string & str) { *this = str; }
		virtual ~Size() {}

		operator double() const { return _size; }
		operator std::string() const { return toString(); }
		Size & operator = (double size) { _size = size; return *this; }
		Size & operator = (const std::string & str);
		Size operator + (const Size & ref) const { return Size(this->_size + ref._size); }
		bool operator < (const Size & ref) const { return _size < ref._size; }

		std::string toString() const;
	private:
		double _size { 0 };
	};
}
