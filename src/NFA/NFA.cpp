#include "NFA.h"

#include <iostream>

using namespace std;

static void PrintSet(const set<int>& s)
{
	cout << "set: ";
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

void NFA::addNode(bool accepted)
{
	edges.push_back(vector<NFAEdge>());
	this->accepted.push_back(accepted);
}

void NFA::addEdge(int index, const NFAEdge& edge)
{
	edges[index].push_back(edge);
}

std::vector<NFAEdge> NFA::getEdges(int index) const
{
	return edges[index];
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
	//cout << toString() << endl;

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
