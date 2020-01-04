#include "Charset.h"

#include <set>

using namespace std;

char Charset::AnyChar = 2;
char Charset::Epsilon = 1;
char Charset::End = 0;

static struct Alphabet
{
	Alphabet()
	{
		//Ìí¼Ó×Ö·û¼¯

		for (char c = 'a'; c <= 'z'; ++c)
		{
			charset.insert(c);
		}

		for (char c = 'A'; c <= 'Z'; ++c)
		{
			charset.insert(c);
		}

		for (char c = '0'; c <= '9'; ++c)
		{
			charset.insert(c);
		}

		char others[] = { '.', '*', '\\', '?', ',', ';', '(', ')', '{', '}', '{', '}', '[', ']', '-', '\'', '_' };
		for (int i = 0; i < (int)sizeof(others) / sizeof(char); ++i)
		{
			charset.insert(others[i]);
		}
	}

	bool inCharset(char ch)
	{
		return charset.count(ch) > 0;
	}

	set<char> charset;
} alphabet;

bool Charset::InCharset(char ch)
{
	return alphabet.inCharset(ch);
}

bool Charset::IsMetaChar(char ch)
{
	return ch == '.' || ch == '\\' || ch == '*' || ch == '(' || ch == ')';
}

const std::set<char>& Charset::GetCharset()
{
	return alphabet.charset;
}
