#pragma once

#include "../NFA/NFA.h"

class Pattern
{
public:
	Pattern(const std::string& input);
	Pattern& compile();
	Pattern& compileToDFA();
	bool match(const std::string& txt);
	std::string toString() const;

private:
	std::string input;
	NFA nfa;
	DFA dfa;
};