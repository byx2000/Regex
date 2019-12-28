#include "RegExpr.h"

#include <iostream>

using namespace std;

Node::~Node()
{

}

RegExpr::RegExpr(Node* p) : p(p)
{
	
}

RegExpr& RegExpr::operator=(Node* p)
{
	this->p.reset(p);
	return *this;
}

std::string RegExpr::toString() const
{
	if (p != NULL)
	{
		return p->toString();
	}
	else
	{
		return "";
	}
}

Char::Char(char ch) : ch(ch)
{

}

std::string Char::toString() const
{
	string s = "";
	s.push_back(ch);
	return s;
}

std::string AnyChar::toString() const
{
	return ".";
}

Concat::Concat(const RegExpr& lhs, const RegExpr& rhs) : lhs(lhs), rhs(rhs)
{
	
}

std::string Concat::toString() const
{
	string s = "&(";
	s += lhs.toString();
	s += ",";
	s += rhs.toString();
	s += ")";
	return s;
}

Choose::Choose(const RegExpr& lhs, const RegExpr& rhs) : lhs(lhs), rhs(rhs)
{

}

std::string Choose::toString() const
{
	string s = "|(";
	s += lhs.toString();
	s += ",";
	s += rhs.toString();
	s += ")";
	return s;
}

StarClosure::StarClosure(const RegExpr& expr) : expr(expr)
{

}

std::string StarClosure::toString() const
{
	string s = "*(";
	s += expr.toString();
	s += ")";
	return s;
}

AddClosure::AddClosure(const RegExpr& expr) : expr(expr)
{

}

std::string AddClosure::toString() const
{
	string s = "+(";
	s += expr.toString();
	s += ")";
	return s;
}
