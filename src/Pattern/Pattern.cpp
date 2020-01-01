#include "Pattern.h"
#include "../Parser/RegExprParser.h"

#include <iostream>

using namespace std;

Pattern::Pattern(const std::string& input) : input(input)
{
	
}

Pattern& Pattern::compile()
{
	if (nfa.empty())
	{
		RegParser parser(input);
		parser.parse(nfa);
	}
	return *this;
}

Pattern& Pattern::compileToDFA()
{
	if (nfa.empty())
	{
		compile();
	}
	nfa.toDFA(dfa);
	return *this;
}

bool Pattern::match(const std::string& txt)
{
	if (!dfa.empty())
	{
		return dfa.match(txt);
	}
	else if (!nfa.empty())
	{
		return nfa.match(txt);
	}
	else
	{
		compile();
		return nfa.match(txt);
	}
}

std::string Pattern::toString() const
{
	string s = "NFA:\n";
	s += nfa.toString();
	s += "\nDFA:\n";
	s += dfa.toString();
	return s;
}
