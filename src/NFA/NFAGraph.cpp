#include "NFAGraph.h"

#include <iostream>

using namespace std;

NFAGraph::NFAGraph()
{
	start = end = NULL;
}

NFAGraph::NFAGraph(char _ch)
{
	start = new State(false);
	end = new State(true);
	start->addTransfer(end, _ch);
}

std::string NFAGraph::toString() const
{
	string s = "begin: ";
	s += to_string((long)start);
	s += "\n";
	s += "end: ";
	s += to_string((long)end);
	s += "\n";
	set<State*> book;
	toString_dfs(start, book, s);
	return s;
}

NFA NFAGraph::toNFA() const
{
	NFA nfa;
	map<State*, int> book;
	int maxIndex = 0;
	toNFA_dfs(start, maxIndex, book, nfa);
	return nfa;
}

void NFAGraph::clear()
{
	if (start != NULL && end != NULL)
	{
		set<State*> book;
		clear_dfs(start, book);
		start = end = NULL;
	}
}

void NFAGraph::toString_dfs(State* cur, std::set<State*>& book, std::string& s) const
{
	s += cur->toString();
	s += "\n";
	book.insert(cur);

	int cnt = cur->getTransferCount();
	for (int i = 0; i < cnt; ++i)
	{
		State* next = cur->getTransferState(i);
		if (book.count(next) == 0)
		{
			toString_dfs(next, book, s);
		}
	}
}

void NFAGraph::clear_dfs(State* cur, std::set<State*>& book)
{
	book.insert(cur);
	int cnt = cur->getTransferCount();
	for (int i = 0; i < cnt; ++i)
	{
		State* next = cur->getTransferState(i);
		if (book.count(next) == 0)
		{
			clear_dfs(next, book);
		}
	}
	delete cur;
}

void NFAGraph::toNFA_dfs(State* cur, int& maxIndex, std::map<State*, int>& book, NFA& nfa) const
{
	book[cur] = maxIndex++;
	nfa.addNode(cur->isAccepted());

	int t = maxIndex;
	int cnt = cur->getTransferCount();
	for (int i = 0; i < cnt; ++i)
	{
		State* next = cur->getTransferState(i);
		char ch = cur->getTransferChar(i);

		if (book.count(next) == 0)
		{
			nfa.addEdge(t - 1, NFAEdge(maxIndex, ch));
			toNFA_dfs(next, maxIndex, book, nfa);
		}
		else
		{
			nfa.addEdge(t - 1, NFAEdge(book[next], ch));
		}
	}
}
