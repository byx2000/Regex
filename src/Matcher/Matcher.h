#pragma once

#include <memory>

class _Matcher;

class Matcher
{
public:
	Matcher(_Matcher* p = NULL);
	bool isMatch(char ch) const;

private:
	std::shared_ptr<_Matcher> p;
};

class _Matcher
{
public:
	virtual bool isMatch(char ch) const = 0;
	virtual ~_Matcher();
};

class CharMatcher : public _Matcher
{
public:
	CharMatcher(char ch);
	virtual bool isMatch(char ch) const override;
private:
	char ch;
};

class AnyCharMatcher : public _Matcher
{
public:
	virtual bool isMatch(char ch) const override;
};