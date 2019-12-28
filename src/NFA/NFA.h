#pragma once

#include "State.h"

class NFA
{
public:
	NFA(char ch);
	State* getStartState() const;
	State* getEndState() const;
	std::string toString() const;

private:
	State* start, * end;

	void toString_dfs(State* cur, std::set<State*>& book, std::string& s) const;
};