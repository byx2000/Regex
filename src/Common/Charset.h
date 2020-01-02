#pragma once

#include <set>

class Charset
{
public:
	char static AnyChar;
	char static Epsilon;
	static bool inCharset(char ch);
	static const std::set<char>& GetCharset();
};