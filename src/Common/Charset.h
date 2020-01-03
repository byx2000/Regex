#pragma once

#include <set>

class Charset
{
public:
	char static AnyChar;
	char static Epsilon;
	static bool InCharset(char ch);
	static bool IsMetaChar(char ch);
	static const std::set<char>& GetCharset();
};