#pragma once

#include "State.h"

class NFAGraph
{
public:
	State* start, * end;

	NFAGraph();
	NFAGraph(char ch);
	std::string toString() const;
	void clear();
	
private:
	void toString_dfs(State* cur, std::set<State*>& book, std::string& s) const;
	void clear_dfs(State* cur, std::set<State*>& book);
};