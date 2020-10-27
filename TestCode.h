#pragma once
class TestCode
{
public:
	TestCode();
	TestCode(const TestCode&) = delete;
	~TestCode();

	void TestLine(MyWindow* _hwnd);
	void TestTimer(MyWindow* _hwnd);
	void TestRenderColour(MyWindow* _hwnd, float _r, float _g, float _b) noexcept;

private:

};

