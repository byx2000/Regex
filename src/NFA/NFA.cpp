#include "NFA.h"

using namespace std;

NFA::NFA(char ch)
{
	end.setAccepted(true);
	start.addTransfer(end, ch);
}

std::string NFA::toString() const
{
	string s;
	s += "start: ";
	s += to_string((long)start.getAddress());
	s += "\n";
	s += "end: ";
	s += to_string((long)end.getAddress());
	s += "\n";
	set<State> book;
	toString_dfs(start, book, s);
	return s;
}

void NFA::concat(NFA& nfa)
{
	end.assign(nfa.start);
	end = nfa.end;
}

void NFA::parallel(NFA& nfa)
{
	State head, tail(true);
	head.addTransfer(start, ' ');
	head.addTransfer(nfa.start, ' ');
	end.addTransfer(tail, ' ');
	nfa.end.addTransfer(tail, ' ');
	end.setAccepted(false);
	nfa.end.setAccepted(false);
	start = head;
	end = tail;
}

void NFA::starClosure()
{
	State head, tail(true);
	head.addTransfer(start, ' ');
	head.addTransfer(tail, ' ');
	end.addTransfer(tail, ' ');
	end.addTransfer(start, ' ');
	end.setAccepted(false);
	start = head;
	end = tail;
}

void NFA::addClosure()
{
	/*State head, tail(true);
	head.addTransfer(start, ' ');
	end.addTransfer(tail, ' ');
	end.addTransfer(start, ' ');
	end.setAccepted(false);
	start = head;
	end = tail;*/

	end.addTransfer(start, ' ');
}

void NFA::toString_dfs(const State& cur, std::set<State>& book, std::string& s) const
{
	s += cur.toString();
	s += "\n";
	book.insert(cur);

	vector<State> next = cur.getNextStates();
	for (int i = 0; i < (int)next.size(); ++i)
	{
		if (book.count(next[i]) == 0)
		{
			toString_dfs(next[i], book, s);
		}
	}
}
