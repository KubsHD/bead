#pragma once

#include <string>
#include <sstream>

namespace bead
{
	template <typename T>
	std::string ts(T x)
	{
		std::stringstream ss;
		ss << x;
		return ss.str();
	}
}