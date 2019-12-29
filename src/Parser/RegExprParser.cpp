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

RegExprParser::~RegExprParser()
{
	nfa.clear();
}

void RegExprParser::setInput(const std::string& input)
{
	this->input = input;
}

void RegExprParser::parse()
{
	index = 0;
	expr = parseExpr();
	nfa.clear();
}

void RegExprParser::toNFA()
{
	nfa = expr.getNFA();
}

RegExpr RegExprParser::getRegExpr() const
{
	return expr;
}

NFAGraph RegExprParser::getNFA() const
{
	return nfa;
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

void RegExprParser::read(char _ch)
{
	if (_ch != next())
	{
		string s = "";
		s.push_back(_ch);
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
	char _ch = peek();
	while (_ch != 0 && _ch != ')' && _ch != '|')
	{
		res = new Concat(res, parseFactor());
		_ch = peek();
	}
	return res;
}

RegExpr RegExprParser::parseFactor()
{
	RegExpr res = parseTerm();
	char _ch = peek();
	if (_ch == '*')
	{
		next();
		return new StarClosure(res);
	}
	else if (_ch == '+')
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
	char _ch = next();
	if (_ch >= 'a' && _ch <= 'z')
	{
		return new Char(_ch);
	}
	else if (_ch == '.')
	{
		return new AnyChar();
	}
	else if (_ch == '(')
	{
		RegExpr res = parseExpr();
		read(')');
		return res;
	}
	else
	{
		string s = "Unexpected character: ";
		s.push_back(_ch);
		throw ParseError(s);
	}
}
