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

NFAGraph RegExpr::getNFA() const
{
	return p->getNFA();
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

NFAGraph Char::getNFA() const
{
	return NFAGraph(ch);
}

std::string AnyChar::toString() const
{
	return ".";
}

NFAGraph AnyChar::getNFA() const
{
	return NFAGraph('.');
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

NFAGraph Concat::getNFA() const
{
	NFAGraph left = lhs.getNFA();
	NFAGraph right = rhs.getNFA();
	*(left.end) = *(right.start);
	delete right.start;
	left.end = right.end;
	return left;
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

NFAGraph Choose::getNFA() const
{
	NFAGraph left = lhs.getNFA();
	NFAGraph right = rhs.getNFA();
	State* head = new State(false);
	State* tail = new State(true);
	head->addTransfer(left.start, ' ');
	head->addTransfer(right.start, ' ');
	left.end->addTransfer(tail, ' ');
	right.end->addTransfer(tail, ' ');
	left.end->setAccepted(false);
	right.end->setAccepted(false);
	left.start = head;
	left.end = tail;
	return left;
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

NFAGraph StarClosure::getNFA() const
{
	NFAGraph nfa = expr.getNFA();
	State* head = new State(false);
	State* tail = new State(true);
	head->addTransfer(nfa.start, ' ');
	head->addTransfer(tail, ' ');
	nfa.end->addTransfer(tail, ' ');
	nfa.end->addTransfer(nfa.start, ' ');
	nfa.end->setAccepted(false);
	nfa.start = head;
	nfa.end = tail;
	return nfa;
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

NFAGraph AddClosure::getNFA() const
{
	NFAGraph nfa = expr.getNFA();
	State* head = new State(false);
	State* tail = new State(true);
	head->addTransfer(nfa.start, ' ');
	nfa.end->addTransfer(tail, ' ');
	nfa.end->addTransfer(nfa.start, ' ');
	nfa.end->setAccepted(false);
	nfa.start = head;
	nfa.end = tail;
	return nfa;
}
