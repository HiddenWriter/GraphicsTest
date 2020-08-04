#include "pch.h"
#include "ExceptionClass.h"

ExceptionClass::ExceptionClass(int line, const char* file) noexcept
	:
	line(line),
	file(file)
{
	return;
}

const char* ExceptionClass::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* ExceptionClass::GetType() const noexcept
{
	return "Exception";
}

int ExceptionClass::GetLine() const noexcept
{
	return line;

}

const std::string& ExceptionClass::GetFile() const noexcept
{
	return file;
}

std::string ExceptionClass::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "\n\t Flie : " << file << "\n"
		<< "\n't line : " << line;
	return oss.str();
}