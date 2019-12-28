#include "NFA.h"

using namespace std;

NFA::NFA()
{
	start = end = NULL;
}

NFA::NFA(char ch)
{
	start = new State(false);
	end = new State(true);
	start->addTransfer(end, ch);
}

std::string NFA::toString() const
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

void NFA::clear()
{
	if (start != NULL && end != NULL)
	{
		set<State*> book;
		clear_dfs(start, book);
		start = end = NULL;
	}
}

void NFA::toString_dfs(State* cur, std::set<State*>& book, std::string& s) const
{
	s += cur->toString();
	s += "\n";
	book.insert(cur);

	vector<State*> next = cur->getNextStates();
	for (int i = 0; i < (int)next.size(); ++i)
	{
		if (book.count(next[i]) == 0)
		{
			toString_dfs(next[i], book, s);
		}
	}
}

void NFA::clear_dfs(State* cur, std::set<State*>& book)
{
	book.insert(cur);
	vector<State*> next = cur->getNextStates();
	for (int i = 0; i < (int)next.size(); ++i)
	{
		if (book.count(next[i]) == 0)
		{
			clear_dfs(next[i], book);
		}
	}
	delete cur;
}
