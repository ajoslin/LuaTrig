#ifndef UTIL_LUA_H_
#define UTIL_LUA_H_

#include <exception>

class UnusableParameterException
{
private:
	char *message;
public:
	UnusableParameterException(const char *ecName, const char *attemptName) 
	{
		message = new char[50];
		sprintf(message, "Effect/Condition %s cannot have a %s parameter.", ecName, attemptName);
	}
	char *what() { return message; }
};


#endif