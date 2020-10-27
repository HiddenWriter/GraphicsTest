#include "pch.h"
#include "Application.h"

Application::Application(const std::string& _cmdLine)
	: mCmdLine(_cmdLine),
	mWnd(1280, 720, "First Game Box")
{
	
}

Application::~Application() { return; }

void Application::HandleInput(float _dt)
{
	while (const auto e = mWnd.mKBD.ReadKey())
	{
		if (!e->IsPressed()) continue;

		switch (e->GetCode())
		{
		case VK_ESCAPE:
			if (mWnd.CursorEnabled())
			{
				mWnd.DisableCursor();
				mWnd.mMouse.EnableRaw();
			}
			else
			{
				mWnd.DisableCursor();
				mWnd.mMouse.DisableRaw();
			}
			break;
		default:
			break;
		}
	}
	return;
}

int Application::Go()
{
	while (1)
	{
		if (const auto ecode = MyWindow::ProcessMessages())
		{
			return *ecode;
		}
		DoFrame(0.0f);
	}
}

void Application::DoFrame(float _dt)
{
	t1.TestLine(&mWnd);
	return;
}
