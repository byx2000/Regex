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

void NFAGraph::concat(NFAGraph& ng)
{
	*end = *(ng.start);
	delete ng.start;
	end = ng.end;
}

void NFAGraph::parallel(NFAGraph& ng)
{
	State* head = new State(false);
	State* tail = new State(true);
	head->addTransfer(start, ' ');
	head->addTransfer(ng.start, ' ');
	end->addTransfer(tail, ' ');
	ng.end->addTransfer(tail, ' ');
	end->setAccepted(false);
	ng.end->setAccepted(false);
	start = head;
	end = tail;
}

void NFAGraph::starClosure()
{
	State* head = new State(false);
	State* tail = new State(true);
	head->addTransfer(start, ' ');
	head->addTransfer(tail, ' ');
	end->addTransfer(tail, ' ');
	end->addTransfer(start, ' ');
	end->setAccepted(false);
	start = head;
	end = tail;
}

void NFAGraph::addClosure()
{
	State* head = new State(false);
	State* tail = new State(true);
	head->addTransfer(start, ' ');
	end->addTransfer(tail, ' ');
	end->addTransfer(start, ' ');
	end->setAccepted(false);
	start = head;
	end = tail;
}

void NFAGraph::toNFA(NFA& nfa) const
{
	nfa.clear();
	map<State*, int> book;
	int maxIndex = 0;
	toNFA_dfs(start, maxIndex, book, nfa);
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
	nfa.addState(cur->isAccepted());

	int t = maxIndex;
	int cnt = cur->getTransferCount();
	for (int i = 0; i < cnt; ++i)
	{
		State* next = cur->getTransferState(i);
		char ch = cur->getTransferChar(i);

		if (book.count(next) == 0)
		{
			nfa.addTransfer(t - 1, maxIndex, ch);
			toNFA_dfs(next, maxIndex, book, nfa);
		}
		else
		{
			nfa.addTransfer(t - 1, book[next], ch);
		}
	}
}
