#pragma once
#include <string>
#include <vector>

class StringConverter
{
public:
	static std::wstring StringToWide(std::string str);
	static std::string StringFromCharVec(std::vector<char> src);
};