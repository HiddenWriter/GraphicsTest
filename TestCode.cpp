#include "pch.h"
#include "TestCode.h"

TestCode::TestCode()
{}
TestCode::~TestCode() {}
void TestCode::TestLine(MyWindow* _hwnd)
{
	if (!_hwnd->mMouse.IsEmpty())
	{
		// Begin Test  
		if (!_hwnd->mMouse.IsEmpty())
		{
			const auto e = _hwnd->mMouse.Read();
			if (e->GetType() == MyMouse::Event::Type::Move)
			{
				std::ostringstream oss;
				oss << "Mouse Position : (" << e->GetPosX() << ", " << e->GetPosY() << ")";
				_hwnd->SetTitle(oss.str());
			}
			if (e->GetType() == MyMouse::Event::Type::Leave)
			{
				float peek = static_cast<float>(_hwnd->mTimer.Peek());
				std::ostringstream oss;
				oss << "Mouse Left Window at : " << peek;
				_hwnd->SetTitle(oss.str());
			}
		}

		
		// End Test

	}
	return;
}

void TestCode::TestTimer(MyWindow* _hwnd)
{
	return;
}

void TestCode::TestRenderColour(MyWindow* _hwnd, float _r, float _g, float _b) noexcept
{
	const float colour = sin(_hwnd->mTimer.Peek()) / 2.0f + 0.5f;
	_hwnd->GetGraphics().ClearBuffer(colour, colour, 0.0f);
	return;
}