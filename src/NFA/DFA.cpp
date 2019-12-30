#include "DFA.h"

using namespace std;

void DFA::addState(bool accepted)
{
	trans.push_back(vector<char>(256, -1));
	this->accepted.push_back(accepted);
}

void DFA::addTransfer(int state, int to, char ch)
{
	trans[state][ch] = to;
}

void DFA::setStateAccepted(int state, bool accepted)
{
	this->accepted[state] = accepted;
}

std::string DFA::toString() const
{
	string s = "";
	for (int i = 0; i < (int)trans.size(); ++i)
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

		for (int j = 0; j < (int)trans[i].size(); ++j)
		{
			if (trans[i][j] != -1)
			{
				s += "(";
				s += to_string(trans[i][j]);
				s += ",";
				s.push_back((char)j);
				s += ") ";
			}
		}

		s += "\n";
	}

	return s;
}
