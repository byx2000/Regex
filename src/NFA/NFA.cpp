#include "NFA.h"

#include <iostream>
#include <map>
#include <queue>

using namespace std;

template<typename T>
static void PrintSet(const set<T>& s)
{
	for (auto i = s.begin(); i != s.end(); ++i)
	{
		cout << *i << " ";
	}
	cout << endl;
}

NFAEdge::NFAEdge(int to, char ch) : _to(to), _ch(ch)
{

}

int NFAEdge::to() const
{
	return _to;
}

char NFAEdge::ch() const
{
	return _ch;
}

std::string NFAEdge::toString() const
{
	string s = "(";
	s += to_string(_to);
	s += ",";
	s.push_back(_ch);
	s += ")";
	return s;
}

void NFA::addState(bool accepted)
{
	edges.push_back(vector<NFAEdge>());
	this->accepted.push_back(accepted);
}

void NFA::addTransfer(int state, int to, char ch)
{
	edges[state].push_back(NFAEdge(to, ch));
}

std::string NFA::toString() const
{
	string s = "";
	for (int i = 0; i < (int)edges.size(); ++i)
	{
		s += to_string(i);
		if (accepted[i])
		{
			s += "(accepted):\t";
		}
		else
		{
			s += "(unaccepted):\t";
		}

		for (int j = 0; j < (int)edges[i].size(); ++j)
		{
			s += edges[i][j].toString();
			s += " ";
		}

		s += "\n";
	}

	return s;
}

bool NFA::match(const std::string& txt) const
{
	set<int> s;
	s.insert(0);
	updateEpsilonClosure(s);

	for (int i = 0; i < (int)txt.size(); ++i)
	{
		updateNextState(s, txt[i]);
		if (s.size() == 0) break;
		updateEpsilonClosure(s);
	}

	for (auto i = s.begin(); i != s.end(); ++i)
	{
		if (accepted[*i])
		{
			return true;
		}
	}

	return false;
}

//子集构造法
DFA NFA::toDFA() const
{
	//获取输入字符集
	set<char> inputSet;
	for (int i = 0; i < (int)edges.size(); ++i)
	{
		for (int j = 0; j < (int)edges[i].size(); ++j)
		{
			char ch = edges[i][j].ch();
			if (ch != ' ')
			{
				inputSet.insert(ch);
			}
		}
	}
	vector<char> inputCharset(inputSet.begin(), inputSet.end());

	DFA dfa;
	set<int> s;
	queue<set<int>> q;
	map<set<int>, int> dState;
	int curIndex = 0;

	s.insert(0);
	updateEpsilonClosure(s);
	dfa.addState(isAccepted(s));
	dState[s] = 0;
	q.push(s);
	curIndex++;

	while (!q.empty())
	{
		set<int> front = q.front();
		q.pop();
		int cur = dState[front];
		
		for (int i = 0; i < (int)inputCharset.size(); ++i)
		{
			char ch = inputCharset[i];
			set<int> t = front;
			getAllTransfer(t, ch);
			
			if (!t.empty())
			{
				if (dState.count(t) != 0)
				{
					dfa.addTransfer(cur, dState[t], ch);
				}
				else
				{
					dfa.addState(isAccepted(t));
					dfa.addTransfer(cur, curIndex, ch);
					dState[t] = curIndex;
					curIndex++;
					q.push(t);
				}
			}
		}
	}

	return dfa;
}

bool NFA::empty() const
{
	return edges.size() == 0;
}

void NFA::updateNextState(std::set<int>& s, char ch) const
{
	set<int> t;
	for (auto i = s.begin(); i != s.end(); ++i)
	{
		for (int j = 0; j < (int)edges[*i].size(); ++j)
		{
			char c = edges[*i][j].ch();
			if (c == '.' || c == ch)
			{
				t.insert(edges[*i][j].to());
			}
		}
	}
	s = t;
}

void NFA::updateEpsilonClosure(std::set<int>& s) const
{
	vector<bool> book(edges.size(), false);
	for (auto i = s.begin(); i != s.end(); ++i)
	{
		epsilonClosure_dfs(*i, book);
	}

	s.clear();
	for (int i = 0; i < (int)book.size(); ++i)
	{
		if (book[i])
		{
			s.insert(i);
		}
	}
}

void NFA::epsilonClosure_dfs(int cur, std::vector<bool>& book) const
{
	book[cur] = true;
	for (int i = 0; i < (int)edges[cur].size(); ++i)
	{
		char ch = edges[cur][i].ch();
		int to = edges[cur][i].to();
		if (ch == ' ' && !book[to])
		{
			epsilonClosure_dfs(to, book);
		}
	}
}

void NFA::getAllTransfer(std::set<int>& s, char ch) const
{
	updateNextState(s, ch);
	if (!s.empty())
	{
		updateEpsilonClosure(s);
	}
}

bool NFA::isAccepted(const std::set<int>& s) const
{
	for (auto i = s.begin(); i != s.end(); ++i)
	{
		if (accepted[*i])
		{
			return true;
		}
	}
	return false;
}
