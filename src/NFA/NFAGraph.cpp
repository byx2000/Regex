#include "NFAGraph.h"
#include "../Common/Charset.h"
#include "../Common/Error.h"

#include <iostream>
#include <stack>
#include <queue>

using namespace std;

NFAGraph::NFAGraph()
{
	start = end = NULL;
}

NFAGraph::NFAGraph(char ch)
{
	start = new State(false);
	end = new State(true);
	if (ch == Charset::AnyChar)
	{
		const set<char>& charset = Charset::GetCharset();
		for (auto i = charset.begin(); i != charset.end(); ++i)
		{
			start->addTransfer(end, *i);
		}
	}
	else
	{
		
		start->addTransfer(end, ch);
	}
}

NFAGraph::NFAGraph(char c1, char c2)
{
	start = new State(false);
	end = new State(true);

	if (c1 > c2)
	{
		string s = "Illegal scope: [";
		s.push_back(c1);
		s.push_back(',');
		s.push_back(c2);
		s.push_back(']');
		throw ParseError(s);
	}

	for (char ch = c1; ch <= c2; ++ch)
	{
		if (!Charset::InCharset(ch))
		{
			string s = "Illegal scope: [";
			s.push_back(c1);
			s.push_back(',');
			s.push_back(c2);
			s.push_back(']');
			throw ParseError(s);
		}

		start->addTransfer(end, ch);
	}
}

NFAGraph::NFAGraph(const vector<char>& chs)
{
	start = new State(false);
	end = new State(true);

	for (int i = 0; i < (int)chs.size(); ++i)
	{
		if (!Charset::InCharset(chs[i]))
		{
			string s = "Unexpected character: ";
			s.push_back(chs[i]);
			throw ParseError(s);
		}

		start->addTransfer(end, chs[i]);
	}
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
	head->addTransfer(start, Charset::Epsilon);
	head->addTransfer(ng.start, Charset::Epsilon);
	end->addTransfer(tail, Charset::Epsilon);
	ng.end->addTransfer(tail, Charset::Epsilon);
	end->setAccepted(false);
	ng.end->setAccepted(false);
	start = head;
	end = tail;
}

void NFAGraph::starClosure()
{
	State* head = new State(false);
	State* tail = new State(true);
	head->addTransfer(start, Charset::Epsilon);
	head->addTransfer(tail, Charset::Epsilon);
	end->addTransfer(tail, Charset::Epsilon);
	end->addTransfer(start, Charset::Epsilon);
	end->setAccepted(false);
	start = head;
	end = tail;
}

void NFAGraph::addClosure()
{
	State* head = new State(false);
	State* tail = new State(true);
	head->addTransfer(start, Charset::Epsilon);
	end->addTransfer(tail, Charset::Epsilon);
	end->addTransfer(start, Charset::Epsilon);
	end->setAccepted(false);
	start = head;
	end = tail;
}

void NFAGraph::toNFA(NFA& nfa) const
{
	//µÝ¹é
	nfa.clear();
	map<State*, int> book;
	int maxIndex = 0;
	toNFA_dfs(start, maxIndex, book, nfa);

	//·ÇµÝ¹é
	/*nfa.clear();
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
	}*/
}

void NFAGraph::clear()
{
	if (start != NULL && end != NULL)
	{
		//cout << toString() << endl;
		//µÝ¹é
		/*set<State*> book;
		clear_dfs(start, book);
		start = end = NULL;*/

		//·ÇµÝ¹é
		stack<State*> s;
		s.push(start);
		set<State*> book;
		while (!s.empty())
		{
			State* cur = s.top();
			s.pop();

			if (book.count(cur) > 0)	 continue;

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
