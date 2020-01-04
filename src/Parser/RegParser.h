#pragma once

#include "../NFA/NFAGraph.h"

class RegParser
{
public:
	RegParser(const std::string& input);
	void setInput(const std::string& input);
	RegParser& parse(NFA& nfa);

private:
	std::string input;
	int index;

	char next();
	char peek();
	void read(char ch);

	NFAGraph parseExpr();
	NFAGraph parseCatExpr();
	NFAGraph parseFactor();
	NFAGraph parseTerm();
	NFAGraph parseScope();
};