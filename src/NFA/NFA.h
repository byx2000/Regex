#pragma once

#include <string>
#include <vector>

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
	void addNode(bool accepted);
	void addEdge(int index, const NFAEdge& edge);
	std::vector<NFAEdge> getEdges(int index) const;
	std::string toString() const;

private:
	std::vector<std::vector<NFAEdge>> edges;
	std::vector<bool> accepted;
};