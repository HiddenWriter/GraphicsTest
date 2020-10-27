#include "pch.h"
#include "MyKeyboard.h"

bool MyKeyboard::KeyIsPressed(unsigned char _keycode) const
{
	return mKeyStates[_keycode];
}

bool MyKeyboard::KeyIsEmpty() const
{
	return mKeyBuffer.empty();
}

bool MyKeyboard::CharIsEmpty() const
{
	return mCharBuffer.empty();
}

bool MyKeyboard::AutoRepeatIsEnabled() const
{
	return mAutoRepeatEnabled;
}

void MyKeyboard::FlushKey()
{
	mKeyBuffer = std::queue <Event>();
	return;
}

void MyKeyboard::FlushChar()
{
	mCharBuffer = std::queue<char>();
	return;
}

void MyKeyboard::Flush()
{
	FlushKey();
	FlushChar();
	return;
}

void MyKeyboard::EnableAutoRepeat()
{
	mAutoRepeatEnabled = true;
	return;
}

void MyKeyboard::DisableAutoRepeat()
{
	mAutoRepeatEnabled = false;
	return;
}

std::optional<MyKeyboard::Event> MyKeyboard::ReadKey()
{
	if (mKeyBuffer.size() > 0u)
	{
		MyKeyboard::Event e = mKeyBuffer.front();
		mKeyBuffer.pop();
		return e;
	}

	return {};
}

std::optional<char> MyKeyboard::ReadChar()
{
	if (mCharBuffer.size() > 0u)
	{
		unsigned char charCode = mCharBuffer.front();
		mCharBuffer.pop();
		return charCode;
	}

	return {};
}

void MyKeyboard::OnKeyPressed(unsigned char _keycode)
{
	mKeyStates[_keycode] = true;
	mKeyBuffer.push(MyKeyboard::Event(MyKeyboard::Event::Type::Press, _keycode));
	TrimBuffer(mKeyBuffer);
	return;
}

void MyKeyboard::OnKeyReleased(unsigned char _keycode)
{
	mKeyStates[_keycode] = false;
	mKeyBuffer.push(MyKeyboard::Event(MyKeyboard::Event::Type::Release, _keycode));
	TrimBuffer(mKeyBuffer);

	return;
}

void MyKeyboard::OnChar(char _char)
{
	mCharBuffer.push(_char);
	TrimBuffer(mCharBuffer);

	return;
}

void MyKeyboard::ClearState()
{
	mKeyStates.reset();

	return;
}

template <typename T>
void MyKeyboard::TrimBuffer(std::queue<T>& _buffer)
{
	while (_buffer.size() > mBufferSize)
	{
		_buffer.pop();
	}

	return;
}