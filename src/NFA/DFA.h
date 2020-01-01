#pragma once

#include <vector>
#include <string>

class DFA
{
public:
	DFA();
	void addState(bool accepted);
	void addTransfer(int state, int to, char ch);
	void setStateAccepted(int state, bool accepted);
	std::string toString() const;
	bool match(const std::string& txt) const;
	bool empty() const;
	void clear();

private:
	std::vector<std::vector<int>> trans;
	std::vector<bool> accepted;
};