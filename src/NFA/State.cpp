#include "State.h"

#include <iostream>

using namespace std;

State::State(bool accepted)
{
	this->accepted = accepted;
}

bool State::isAccepted() const
{
	return accepted;
}

void State::setAccepted(bool accepted)
{
	this->accepted = accepted;
}

void State::addTransfer(State* state, char _ch)
{
	next.push_back(state);
	chs.push_back(_ch);
}

int State::getTransferCount() const
{
	return next.size();
}

State* State::getTransferState(int index) const
{
	return next[index];
}

char State::getTransferChar(int index) const
{
	return chs[index];
}

std::string State::toString() const
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
		s += to_string((long)next[i]);
		s += ",";
		s.push_back(chs[i]);
		s += ") ";
	}

	return s;
}
