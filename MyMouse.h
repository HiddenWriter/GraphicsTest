#pragma once
class MyMouse
{
	friend class MyWindow;
public:
	struct RawDelta
	{
		int x, y;
	};
	class Event
	{
	public:
		enum class Type
		{
			LPress,
			LRelease,
			RPress,
			RRelease,
			WheelUp,
			WheelDown,
			Move,
			Enter,
			Leave
		};
	public:
		Event(Type _type, const MyMouse& _parent) noexcept
			: mType(_type), 
			mLeftIsPressed(_parent.mLeftIsPressed), 
			mRightIsPressed(_parent.mRightIsPressed),
			mX(_parent.mX),
			mY(_parent.mY)
		{}
		Type GetType() const noexcept
		{
			return mType;
		}
		std::pair<int, int> GetPos() const noexcept
		{
			return { mX, mY };
		}
		int GetPosX() const noexcept
		{
			return mX;
		}
		int GetPosY() const noexcept
		{
			return mY;
		}
		bool LeftIsPressed() const noexcept
		{
			return mLeftIsPressed;
		}
		bool RightIsPressed() const noexcept
		{
			return mRightIsPressed;
		}
	private:
		Type mType;
		bool mLeftIsPressed;
		bool mRightIsPressed;
		int mX, mY;
	};
public:
	MyMouse() = default;
	MyMouse(const MyMouse&) = delete;
	MyMouse& operator=(const MyMouse&) = delete;

	std::pair<int, int> GetPos() const noexcept;

	std::optional<RawDelta> ReadRawDelta() noexcept;

	int GetPosX() const noexcept;

	int GetPosY() const noexcept;

	bool IsInWindow() const noexcept;

	bool LeftIsPressed() const noexcept;

	bool RightIsPressed() const noexcept;

	std::optional<MyMouse::Event> Read() noexcept;

	bool IsEmpty() const noexcept;

	void Flush() noexcept;

	void EnableRaw() noexcept;

	void DisableRaw() noexcept;

	bool RawEnabled() const noexcept;

private:
	
	void OnMouseMove(int _x, int _y) noexcept;

	void OnMouseLeave() noexcept;

	void OnMouseEnter() noexcept;

	void OnRawDelta(int _dx, int _dy) noexcept;

	void OnLeftIsPressed(int _x, int _y) noexcept;

	void OnLeftIsReleased(int _x, int _y) noexcept;

	void OnRightIsPressed(int _x, int _y) noexcept;

	void OnRightIsReleased(int _x, int _y) noexcept;

	void OnWheelUp(int _x, int _y) noexcept;

	void OnWheelDown(int _x, int _y) noexcept;

	void TrimBuffer() noexcept;

	void TrimRawInputBuffer() noexcept;

	void OnWheelDelta(int _x, int _y, int _delta) noexcept;
private:
	static constexpr unsigned int mBufferSize = 16u;
	bool mLeftIsPressed = false;
	bool mRightIsPressed = false;
	bool mIsInWindow = false;
	bool mRawEnabled = false;	
	int mX;
	int mY;
	int mWheelDeltaCarry = 0;
	std::queue<Event> mBuffer;
	std::queue<RawDelta> mRawDeltaBuffer;


};

