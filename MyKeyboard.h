#pragma once
class MyKeyboard
{

	friend class MyWindow;

public:

	class Event
	{
	public:
		enum class Type
		{
			Press,
			Release,
			Invalid
		};
	
	public:

		Event()
			: mType(Type::Invalid), mCode(0u)
		{
			return;
		}

		Event(Type _type, unsigned char _code)
			:	mType(_type), mCode(_code)
		{
			return;
		}

		bool IsPressed() const
		{
			return mType == Type::Press;
		}

		bool IsReleased() const
		{
			return mType == Type::Release;
		}
		
		unsigned char GetCode() const
		{
			return mCode;
		}

	private:

		Type mType;
		unsigned char mCode;

	};

public:

	MyKeyboard() = default;

	MyKeyboard(const MyKeyboard&) = delete;

	MyKeyboard& operator=(const MyKeyboard&) = delete;

	std::optional<char> ReadChar();

	std::optional<MyKeyboard::Event> ReadKey();

	bool KeyIsPressed(unsigned char _keycode) const;

	bool KeyIsEmpty() const;

	bool CharIsEmpty() const;

	bool AutoRepeatIsEnabled() const;

	void FlushChar();

	void Flush();

	void FlushKey();

	void EnableAutoRepeat();

	void DisableAutoRepeat();

private:

	// Functions for MyWindow as these are friend of MyWindow class 

	void OnKeyPressed(unsigned char _keycode);

	void OnKeyReleased(unsigned char _keycode);

	void OnChar(char _char);

	void ClearState();

	template <typename T>
	static void TrimBuffer(std::queue<T>& _buffer);

private:

	static constexpr unsigned int mUKeys = 256u;
	static constexpr unsigned int mBufferSize = 16u;
	std::bitset<mUKeys> mKeyStates;
	std::queue<Event> mKeyBuffer;
	std::queue<char> mCharBuffer;
	bool mAutoRepeatEnabled = false;

};

