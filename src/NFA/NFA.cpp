#include "NFA.h"

using namespace std;

NFA::NFA(char ch)
{
	start = new State(false);
	end = new State(true);
	start->addTransfer(end, ch);
}

State* NFA::getStartState() const
{
	return start;
}

State* NFA::getEndState() const
{
	return end;
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

void NFA::toString_dfs(State* cur, std::set<State*>& book, std::string& s) const
{
	s += cur->toString();
	s += "\n";

	vector<State*> next = cur->getNextStates();
	for (int i = 0; i < (int)next.size(); ++i)
	{
		if (book.count(next[i]) == 0)
		{
			toString_dfs(next[i], book, s);
		}
	}
}
