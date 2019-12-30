#include "Pattern.h"
#include "../Parser/RegExprParser.h"

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

bool Pattern::match(const std::string& txt)
{
	return nfa.match(txt);
}

std::string Pattern::toString() const
{
	return nfa.toString();
}
