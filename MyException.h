#pragma once
class MyException : public std::exception
{

public:

	MyException(int _line, const char* _file);
	virtual const char* What() const;
	virtual const char* GetType() const;
	int GetLine() const;
	const std::string& GetFile() const;
	std::string GetOriginString() const;

private:

	int mLine;
	std::string mFile;

protected:

	mutable std::string mWhatBuffer;

};

