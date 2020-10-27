#include "pch.h"
#include "MyException.h"

MyException::MyException(int _line, const char* _file)
	:mLine(_line), mFile(_file)
{
	return;
}

const char* MyException::What() const
{
	std::ostringstream oss;

	oss << GetType() << "\n"
		<< GetOriginString() << "\n";
	mWhatBuffer = oss.str();

	return mWhatBuffer.c_str();
}

const char* MyException::GetType() const
{
	return "MY EXCEPTION";
}

int MyException::GetLine() const
{
	return mLine;
}

const std::string& MyException::GetFile() const
{
	return mFile;
}

std::string MyException::GetOriginString() const
{
	std::ostringstream oss;

	oss << "\n\t FILE : " << mFile << "\n"
		<< "\n\t LINE :" << mLine << "\n";

	return oss.str();
}