#include "Pattern.h"
#include "../Parser/RegExprParser.h"

#include <iostream>

using namespace std;

Pattern::Pattern(const std::string& input) : input(input)
{
	RegExprParser parser(input);
	RegExpr expr = parser.parse().getRegExpr();
	NFAGraph ng = expr.getNFAGraph();
	nfa = ng.toNFA();
	ng.clear();
}

Pattern& Pattern::compile()
{
	RegExprParser parser(input);
	RegExpr expr = parser.parse().getRegExpr();
	NFAGraph ng = expr.getNFAGraph();
	nfa = ng.toNFA();
	ng.clear();
	return *this;
}

Pattern& Pattern::compileToDFA()
{
	if (nfa.empty())
	{
		compile();
	}
	dfa = nfa.toDFA();
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
	return nfa.toString();
}
