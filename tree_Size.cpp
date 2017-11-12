#include "headers.h"
#include "tree_Size.h"

#include <sstream>
#include <regex>
#include <iomanip>

#ifdef _DEBUG
#define new DBG_NEW
#endif

using namespace tree;

std::string tree::Size::toString() const
{
	std::stringstream str;

	str << std::noshowpoint << std::setprecision(4);

	double size = _size;

	if (size > 1024.)
	{
		size /= 1024.;
		if (size > 1024.)
		{
			size /= 1024.;
			if (size > 1024.)
			{
				str << size / 1024 << "GB";
			}
			else
			{
				str << size << "MB";
			}
		}
		else
		{
			str << size << "kB";
		}
	}
	else
	{
		str << (size_t)size;
	}

	return str.str();

}

tree::Size & tree::Size::operator = (const std::string & str)
{
	std::regex rgx { "([0-9.]+)(kB|B|MB|GB){0,1}" };
	std::smatch match;

	if (std::regex_match(str, match, rgx))
	{
		_size = atof(match[1].str().c_str());

		std::string unit = match[2];
		if (unit == "kB")
			_size *= 1024;
		else if (unit == "MB")
			_size *= 1024 * 1024;
		else if (unit == "GB")
			_size *= 1024 * 1024 * 1024;
		else if (match[2].matched && unit != "B")
			_size = -1.;
	}
	else
	{
		_size = -1;
	}

	return *this;
}
