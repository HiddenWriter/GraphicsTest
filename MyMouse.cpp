#include "pch.h"
#include "MyMouse.h"

std::pair<int, int>	MyMouse::GetPos() const noexcept
{
	return { mX, mY };
}

std::optional<MyMouse::RawDelta> MyMouse::ReadRawDelta() noexcept
{
	if (mRawDeltaBuffer.empty())
	{
		return std::nullopt;
	}
	const RawDelta d = mRawDeltaBuffer.front();
	mRawDeltaBuffer.pop();
	return d;
}

int MyMouse::GetPosX() const noexcept
{
	return mX;
}

int MyMouse::GetPosY() const noexcept
{
	return mY;
}

bool MyMouse::IsInWindow() const noexcept
{
	return mIsInWindow;
}

bool MyMouse::LeftIsPressed() const noexcept
{
	return mLeftIsPressed;
}

bool MyMouse::RightIsPressed() const noexcept
{
	return mRightIsPressed;
}

std::optional<MyMouse::Event> MyMouse::Read() noexcept
{
	if (mBuffer.size() > 0u)
	{
		MyMouse::Event e = mBuffer.front();
		mBuffer.pop();
		return e;
	}
	else return {};
}

bool MyMouse::IsEmpty() const noexcept
{
	return mBuffer.empty();
}

void MyMouse::Flush() noexcept
{
	mBuffer = std::queue<Event>();
	return;
}

void MyMouse::EnableRaw() noexcept
{
	mRawEnabled = true;
	return;
}

void MyMouse::DisableRaw() noexcept
{
	mRawEnabled = false;
	return;
}

bool MyMouse::RawEnabled() const noexcept
{
	return mRawEnabled;
}

void MyMouse::OnMouseMove(int _x, int _y) noexcept
{
	mX = _x;
	mY = _y;
	mBuffer.push(MyMouse::Event(MyMouse::Event::Type::Move, *this));
	TrimBuffer();
	return;
}

void MyMouse::OnMouseLeave() noexcept
{
	mIsInWindow = false;
	mBuffer.push(MyMouse::Event(MyMouse::Event::Type::Leave, *this));
	TrimBuffer();
	return;
}

void MyMouse::OnMouseEnter() noexcept
{
	mIsInWindow = true;
	mBuffer.push(MyMouse::Event(MyMouse::Event::Type::Enter, *this));
	TrimBuffer();
	return;
}

void MyMouse::OnRawDelta(int _dx, int _dy) noexcept
{
	mRawDeltaBuffer.push({ _dx, _dy });
	TrimBuffer();
	return;
}

void MyMouse::OnLeftIsPressed(int _x, int _y) noexcept
{
	mLeftIsPressed = true;
	mBuffer.push(MyMouse::Event(MyMouse::Event::Type::LPress, *this));
	TrimBuffer();
	return;
}

void MyMouse::OnLeftIsReleased(int _x, int _y) noexcept
{
	mLeftIsPressed = false;
	mBuffer.push(MyMouse::Event(MyMouse::Event::Type::LRelease, *this));
	TrimBuffer();
	return;
}

void MyMouse::OnRightIsPressed(int _x, int _y) noexcept
{
	mRightIsPressed = true;
	mBuffer.push(MyMouse::Event(MyMouse::Event::Type::RPress, *this));
	TrimBuffer();
	return;
}

void MyMouse::OnRightIsReleased(int _x, int _y)  noexcept
{
	mRightIsPressed = false;
	mBuffer.push(MyMouse::Event(MyMouse::Event::Type::RRelease, *this));
	TrimBuffer();
	return;
}

void MyMouse::OnWheelDown(int _x, int _y) noexcept
{
	mBuffer.push(MyMouse::Event(MyMouse::Event::Type::WheelDown, *this));
	TrimBuffer();
	return;
}

void MyMouse::OnWheelUp(int _x, int _y) noexcept
{
	mBuffer.push(MyMouse::Event(MyMouse::Event::Type::WheelUp, *this));
	TrimBuffer();
	return;
}

void MyMouse::TrimBuffer() noexcept
{
	while (mBuffer.size() > mBufferSize)
	{
		mBuffer.pop();
	}

	return;
}

void MyMouse::TrimRawInputBuffer() noexcept
{
	while (mRawDeltaBuffer.size() > mBufferSize)
	{
		mRawDeltaBuffer.pop();
	}

	return;
}

void MyMouse::OnWheelDelta(int _x, int _y, int _delta) noexcept
{
	mWheelDeltaCarry += _delta;
	while (mWheelDeltaCarry >= WHEEL_DELTA)
	{
		mWheelDeltaCarry -= WHEEL_DELTA;
		OnWheelUp(_x, _y);
	}
	while (mWheelDeltaCarry <= WHEEL_DELTA)
	{
		mWheelDeltaCarry += WHEEL_DELTA;
		OnWheelDown(_x, _y);
	}
}
