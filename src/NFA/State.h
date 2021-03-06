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
	int getTransferCount() const;
	State* getTransferState(int index) const;
	char getTransferChar(int index) const;

	std::string toString() const;

private:
	std::vector<State*> next;
	std::vector<char> chs;
	bool accepted;
};