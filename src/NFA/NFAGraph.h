#pragma once

#include "State.h"
#include "NFA.h"

#include <map>

class NFAGraph
{
public:
	State* start, * end;

	NFAGraph();
	NFAGraph(char _ch);
	std::string toString() const;
	void concat(NFAGraph& ng);
	void parallel(NFAGraph& ng);
	void starClosure();
	void addClosure();
	void toNFA(NFA& nfa) const;
	void clear();
	
private:
	void toString_dfs(State* cur, std::set<State*>& book, std::string& s) const;
	void clear_dfs(State* cur, std::set<State*>& book);
	void toNFA_dfs(State* cur, int& maxIndex, std::map<State*, int>& book, NFA& nfa) const;
};