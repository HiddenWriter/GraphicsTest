#pragma once
class TestCode
{
public:
	TestCode();
	TestCode(const TestCode&) = delete;
	~TestCode();

	void TestLine(MyWindow* _hwnd);
	void TestTimer(MyWindow* _hwnd);
private:

};

