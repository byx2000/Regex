#include "NFA.h"
#include "../Common/Charset.h"

#include <iostream>
#include <map>
#include <queue>
#include <stack>

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

NFAEdge::NFAEdge(int to, char ch) : to(to), ch(ch)
{
	
}

std::string NFAEdge::toString() const
{
	string s = "(";
	s += to_string(to);
	s += ",";
	s.push_back(ch);
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
void NFA::toDFA(DFA& dfa) const
{
	//获取输入字符集
	set<char> inputSet;
	getInputSet(inputSet);
	vector<char> inputCharset(inputSet.begin(), inputSet.end());

	dfa.clear();
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
}

bool NFA::empty() const
{
	return edges.size() == 0;
}

void NFA::clear()
{
	edges.clear();
	accepted.clear();
}

void NFA::updateNextState(std::set<int>& s, char ch) const
{
	set<int> t;
	for (auto i = s.begin(); i != s.end(); ++i)
	{
		for (int j = 0; j < (int)edges[*i].size(); ++j)
		{
			char c = edges[*i][j].ch;
			if (c == ch)
			{
				t.insert(edges[*i][j].to);
			}
		}
	}
	s = t;
}

void NFA::updateEpsilonClosure(std::set<int>& s) const
{
	//递归
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

	//非递归
	/*vector<bool> book(edges.size(), false);
	stack<int> sta;
	set<int> t;
	for (auto i = s.begin(); i != s.end(); ++i)
	{
		int index = *i;
		if (!book[index])
		{
			sta.push(index);
			while (!sta.empty())
			{
				int cur = sta.top();
				sta.pop();
				book[cur] = true;
				t.insert(cur);

				for (int j = 0; j < (int)edges[cur].size(); ++j)
				{
					int to = edges[cur][j].to;
					int ch = edges[cur][j].ch;
					if (ch == Charset::Epsilon && !book[to])
					{
						sta.push(to);
					}
				}
			}
		}
	}

	s = t;*/
}

void NFA::epsilonClosure_dfs(int cur, std::vector<bool>& book) const
{
	book[cur] = true;
	for (int i = 0; i < (int)edges[cur].size(); ++i)
	{
		char ch = edges[cur][i].ch;
		int to = edges[cur][i].to;
		if (ch == Charset::Epsilon && !book[to])
		{
			epsilonClosure_dfs(to, book);
		}
	}
}

void NFA::getInputSet(std::set<char>& inputSet) const
{
	for (int i = 0; i < (int)edges.size(); ++i)
	{
		for (int j = 0; j < (int)edges[i].size(); ++j)
		{
			char ch = edges[i][j].ch;
			if (ch != Charset::Epsilon)
			{
				inputSet.insert(ch);
			}
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
