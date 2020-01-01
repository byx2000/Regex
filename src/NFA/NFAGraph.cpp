#include "NFAGraph.h"

#include <iostream>
#include <stack>
#include <queue>

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
	/*nfa.clear();
	map<State*, int> book;
	int maxIndex = 0;
	toNFA_dfs(start, maxIndex, book, nfa);*/

	nfa.clear();
	map<State*, int> book;
	stack<State*> s;
	s.push(start);
	int maxIndex = 0;
	while (!s.empty())
	{
		State* cur = s.top();
		s.pop();
		
		book[cur] = maxIndex++;
		nfa.addState(cur->isAccepted());

		int cnt = cur->getTransferCount();
		for (int i = 0; i < cnt; ++i)
		{
			State* next = cur->getTransferState(i);

			if (book.count(next) == 0)
			{
				s.push(next);
			}
		}
	}

	s = stack<State*>();
	set<State*> book2;
	s.push(start);
	while (!s.empty())
	{
		State* cur = s.top();
		s.pop();

		book2.insert(cur);

		int cnt = cur->getTransferCount();
		for (int i = 0; i < cnt; ++i)
		{
			State* next = cur->getTransferState(i);
			char ch = cur->getTransferChar(i);
			nfa.addTransfer(book[cur], book[next], ch);

			if (book2.count(next) == 0)
			{
				s.push(next);
			}
		}
	}
	
}

void NFAGraph::clear()
{
	if (start != NULL && end != NULL)
	{
		/*set<State*> book;
		clear_dfs(start, book);
		start = end = NULL;*/

		stack<State*> s;
		s.push(start);
		set<State*> book;
		while (!s.empty())
		{
			State* cur = s.top();
			s.pop();
			book.insert(cur);

			int cnt = cur->getTransferCount();
			for (int i = 0; i < cnt; ++i)
			{
				State* next = cur->getTransferState(i);

				if (book.count(next) == 0)
				{
					s.push(next);
				}
			}

			delete cur;
		}
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
