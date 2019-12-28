#include "RegExprParser.h"

#include <iostream>

using namespace std;

ParseError::ParseError(const std::string& msg) : msg(msg)
{

}

std::string ParseError::info() const
{
	return msg;
}

RegExprParser::RegExprParser(const std::string& input) : input(input), index(0)
{

}

void RegExprParser::setInput(const std::string& input)
{
	this->input = input;
}

void RegExprParser::parse()
{
	index = 0;
	expr = parseExpr();
}

RegExpr RegExprParser::getRegExpr() const
{
	return expr;
}

char RegExprParser::next()
{
	if (index == input.size())
	{
		return 0;
	}
	return input[index++];
}

char RegExprParser::peek()
{
	if (index == input.size())
	{
		return 0;
	}
	return input[index];
}

void RegExprParser::read(char ch)
{
	if (ch != next())
	{
		string s = "";
		s.push_back(ch);
		s += " expected.";
		throw ParseError(s);
	}
}

RegExpr RegExprParser::parseExpr()
{
	RegExpr res = parseCatExpr();
	while (peek() == '|')
	{
		next();
		res = new Choose(res, parseCatExpr());
	}
	return res;
}

RegExpr RegExprParser::parseCatExpr()
{
	RegExpr res = parseFactor();
	char ch = peek();
	while (ch != 0 && ch != ')' && ch != '|')
	{
		res = new Concat(res, parseFactor());
		ch = peek();
	}
	return res;
}

RegExpr RegExprParser::parseFactor()
{
	RegExpr res = parseTerm();
	char ch = peek();
	if (ch == '*')
	{
		next();
		return new StarClosure(res);
	}
	else if (ch == '+')
	{
		next();
		return new AddClosure(res);
	}
	else
	{
		return res;
	}
}

RegExpr RegExprParser::parseTerm()
{
	char ch = next();
	if (ch >= 'a' && ch < 'z')
	{
		return new Char(ch);
	}
	else if (ch == '.')
	{
		return new AnyChar();
	}
	else if (ch == '(')
	{
		RegExpr res = parseExpr();
		read(')');
		return res;
	}
	else
	{
		string s = "Unexpected character: ";
		s.push_back(ch);
		throw ParseError(s);
	}
}
