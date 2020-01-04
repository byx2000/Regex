#pragma once

#include "State.h"
#include "NFA.h"

#include <map>

class NFAGraph
{
public:
	NFAGraph();
	NFAGraph(char ch);
	NFAGraph(char c1, char c2);
	NFAGraph(const std::vector<char>& chs);
	NFAGraph(const std::vector<std::pair<char, char>>& scopes);
	std::string toString() const;
	void concat(NFAGraph& ng);
	void parallel(NFAGraph& ng);
	void starClosure();
	void addClosure();
	void toNFA(NFA& nfa) const;
	void clear();
	
private:
	State* start, * end;

	void toString_dfs(State* cur, std::set<State*>& book, std::string& s) const;
	void clear_dfs(State* cur, std::set<State*>& book);
	void toNFA_dfs(State* cur, int& maxIndex, std::map<State*, int>& book, NFA& nfa) const;
};