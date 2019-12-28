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
	void parse();
	RegExpr getRegExpr() const;

private:
	std::string input;
	RegExpr expr;
	int index;

	char next();
	char peek();
	void read(char ch);

	RegExpr parseExpr();
	RegExpr parseCatExpr();
	RegExpr parseFactor();
	RegExpr parseTerm();
};