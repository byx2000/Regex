#pragma once

#include "State.h"

class NFA
{
public:
	NFA(char ch);
	std::string toString() const;
	void concat(NFA& nfa);
	void parallel(NFA& nfa);
	void starClosure();
	void addClosure();
private:
	State start, end;

	void toString_dfs(const State& cur, std::set<State>& book, std::string& s) const;
};