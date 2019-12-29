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

	void setInput(const std::string& input);
	RegExprParser& parse();
	RegExpr getRegExpr() const;

private:
	std::string input;
	int index;
	RegExpr expr;

	char next();
	char peek();
	void read(char _ch);

	RegExpr parseExpr();
	RegExpr parseCatExpr();
	RegExpr parseFactor();
	RegExpr parseTerm();
};