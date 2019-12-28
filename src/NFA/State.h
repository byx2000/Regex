#pragma once

#include <memory>
#include <vector>
#include <string>
#include <set>

class _State;

class State
{
public:
	State(bool accepted = false);
	std::string toString() const;
	bool operator<(const State& s) const;
	void addTransfer(const State& s, char ch);
	bool isAccepted() const;
	void setAccepted(bool accepted);
	_State* getAddress() const;
	void assign(const State& s);
	std::vector<State> getNextStates() const;

private:
	std::shared_ptr<_State> p;
};

class _State
{
public:
	_State(bool accepted = false);
	std::string toString() const;
	void addTransfer(const State& s, char ch);
	bool isAccepted() const;
	void setAccepted(bool accepted);
	std::set<State> getNextStates(char ch) const;
	std::vector<State> getNextStates() const;

private:
	std::vector<State> next;
	std::vector<char> chs;
	bool accepted;
};