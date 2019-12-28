#include "State.h"

#include <iostream>

using namespace std;

State::State(bool accepted) : p(new _State(accepted))
{

}

void State::addTransfer(const State& s, char ch)
{
	p->addTransfer(s, ch);
}

bool State::isAccepted() const
{
	return p->isAccepted();
}

void State::setAccepted(bool accepted)
{
	p->setAccepted(accepted);
}

_State* State::getAddress() const
{
	return &(*p);
}

void State::assign(const State& s)
{
	*p = *(s.p);
}

std::vector<State> State::getNextStates() const
{
	return p->getNextStates();
}

std::string State::toString() const
{
	return p->toString();
}

bool State::operator<(const State& s) const
{
	return p < s.p;
}

_State::_State(bool accepted) : accepted(accepted)
{

}

void _State::addTransfer(const State& s, char ch)
{
	next.push_back(s);
	chs.push_back(ch);
}

bool _State::isAccepted() const
{
	return accepted;
}

void _State::setAccepted(bool accepted)
{
	this->accepted = accepted;
}

set<State> _State::getNextStates(char ch) const
{
	set<State> nextStates;
	for (int i = 0; i < (int)chs.size(); ++i)
	{
		if (chs[i] == ch || chs[i] == '.')
		{
			nextStates.insert(next[i]);
		}
	}
	return nextStates;
}

std::vector<State> _State::getNextStates() const
{
	return next;
}

std::string _State::toString() const
{
	string s = to_string((long)this);
	if (accepted)
	{
		s += "(accepted)";
	}
	else
	{
		s += "(unaccepted)";
	}
	s += ":\t";
	for (int i = 0; i < (int)next.size(); ++i)
	{
		s += "(";
		s += to_string((long)next[i].getAddress());
		s += ",";
		s.push_back(chs[i]);
		s += ") ";
	}
	return s;
}
