#pragma once

#include "DFA.h"

#include <set>

class NFAEdge
{
public:
	NFAEdge(int _to, char _ch);
	int to() const;
	char ch() const;
	std::string toString() const;
private:
	int _to;
	char _ch;
};

class NFA
{
public:
	void addState(bool accepted);
	void addTransfer(int state, int to, char ch);
	std::string toString() const;
	bool match(const std::string& txt) const;
	DFA toDFA() const;
	bool empty() const;
	void clear();

private:
	std::vector<std::vector<NFAEdge>> edges;
	std::vector<bool> accepted;

	void updateNextState(std::set<int>& s, char ch) const;
	void updateEpsilonClosure(std::set<int>& s) const;
	void epsilonClosure_dfs(int cur, std::vector<bool>& book) const;
	void getInputSet(std::set<char>& inputSet) const;
	void getAllTransfer(std::set<int>& s, char ch) const;
	bool isAccepted(const std::set<int>& s) const;
};