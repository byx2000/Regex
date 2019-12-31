#include "Matcher.h"

Matcher::Matcher(_Matcher* p) : p(p)
{

}

bool Matcher::isMatch(char ch) const
{
	return p->isMatch(ch);
}

_Matcher::~_Matcher()
{

}

CharMatcher::CharMatcher(char ch) : ch(ch)
{

}

bool CharMatcher::isMatch(char ch) const
{
	return this->ch == ch;
}

bool AnyCharMatcher::isMatch(char ch) const
{
	return ch >= 'a' && ch <= 'z';
}
