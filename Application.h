#pragma once
class Application
{
public:
	Application(const std::string& _cmdLine = "");
	Application(const Application&) = delete;
	int Go();

	~Application();

private:
	void DoFrame(float _dt);

	void HandleInput(float _dt);
private:
	std::string mCmdLine;
	MyWindow mWnd;

	TestCode t1;
};

