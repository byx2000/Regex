#pragma once

#include <vector>
#include <string>

class DFA
{
public:
	void addState(bool accepted);
	void addTransfer(int state, int to, char ch);
	void setStateAccepted(int state, bool accepted);
	std::string toString() const;

private:
	std::vector<std::vector<char>> trans;
	std::vector<bool> accepted;
};