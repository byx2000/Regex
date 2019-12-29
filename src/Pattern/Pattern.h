#pragma once

#include "../NFA/NFA.h"

class Pattern
{
public:
	Pattern(const std::string& input);
	Pattern& compile();
	bool match(const std::string& txt);

private:
	std::string input;
	NFA nfa;
};