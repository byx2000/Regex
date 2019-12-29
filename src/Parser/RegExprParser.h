#pragma once

#include "RegExpr.h"

#include <string>

class ParseError
{
public:
	ParseError(const std::string& msg);
	std::string info() const;
private:
	std::string msg;
};

class RegExprParser
{
public:
	RegExprParser(const std::string& input = "");
	~RegExprParser();

	void setInput(const std::string& input);
	void parse();
	void toNFA();
	RegExpr getRegExpr() const;
	NFAGraph getNFA() const;

private:
	std::string input;
	int index;
	RegExpr expr;
	NFAGraph nfa;

	char next();
	char peek();
	void read(char ch);

	RegExpr parseExpr();
	RegExpr parseCatExpr();
	RegExpr parseFactor();
	RegExpr parseTerm();
};