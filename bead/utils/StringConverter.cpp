#include "StringConverter.h"

std::wstring StringConverter::StringToWide(std::string str)
{
	std::wstring wide_string(str.begin(), str.end());
	return wide_string;
}

std::string StringConverter::StringFromCharVec(std::vector<char> src)
{
	return std::string(src.begin(), src.end());
}
