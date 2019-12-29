#pragma once

#include <vector>
#include <string>
#include <set>

class State
{
public:
	State(bool accepted);
	bool isAccepted() const;
	void setAccepted(bool accepted);
	void addTransfer(State* state, char _ch);
	std::vector<State*> getNextStates() const;
	std::vector<State*> getNextStates(char _ch) const;

	std::string toString() const;

private:
	std::vector<State*> next;
	std::vector<char> chs;
	bool accepted;
};