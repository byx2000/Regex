#pragma once

#include "../NFA/NFAGraph.h"

class ParseError
{
public:
	ParseError(const std::string& msg);
	std::string info() const;
private:
	std::string msg;
};

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
};