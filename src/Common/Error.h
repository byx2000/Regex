#pragma once

#include <string>

class ParseError
{
public:
	ParseError(const std::string& msg);
	std::string info() const;
private:
	std::string msg;
};