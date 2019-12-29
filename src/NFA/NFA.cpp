#include "NFA.h"

using namespace std;

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
