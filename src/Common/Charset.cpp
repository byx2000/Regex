#include "Charset.h"

#include <set>

using namespace std;

char Charset::AnyChar = 0;
char Charset::Epsilon = 1;

static struct Alphabet
{
	Alphabet()
	{
		for (char c = 'a'; c <= 'z'; ++c)
		{
			charset.insert(c);
		}
	}

	bool inCharset(char ch)
	{
		return charset.count(ch) > 0;
	}

	set<char> charset;
} alphabet;

bool Charset::inCharset(char ch)
{
	return alphabet.inCharset(ch);
}

const std::set<char>& Charset::GetCharset()
{
	return alphabet.charset;
}
