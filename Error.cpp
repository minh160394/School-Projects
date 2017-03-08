#include "Error.h"
#include <cstring>
#include <iostream>

namespace ict{
	Error::Error()
	{
		message_ = nullptr;
	}
	Error::Error(const char * Error)
	{
		message_ = nullptr;
		message(Error);
	}
	Error & Error::operator=(const char * errorMessage)
	{
		
		delete [] message_;
		message_ = new char[strlen(errorMessage) + 1];
		strcpy(message_, errorMessage);
		return *this;
		// TODO: insert return statement here
	}
	Error::~Error()
	{
		delete[] message_;
	}
	void Error::clear()
	{
		delete[] message_;
		message_ = nullptr;
	}
	bool Error::isClear() const
	{
		return message_ == nullptr;
	}
	void Error::message(const char * value)
	{
		
		delete[] message_;
		message_ = new char[strlen(value) + 1];
		strcpy(message_, value);
	}
	const char * Error::message() const
	{
		return message_;
	}
	std::ostream & operator<<(std::ostream & os, const Error & s)
	{
		if(s.isClear()){}
		else
		{
			os << s.message();
		}
		return os;
	}

}