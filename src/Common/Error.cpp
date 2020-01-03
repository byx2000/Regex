#include "Error.h"

using namespace std;

ParseError::ParseError(const std::string& msg) : msg(msg)
{

}

std::string ParseError::info() const
{
	return msg;
}