#pragma once
class MyWindow
{
public:

	MyWindow(int _width, int _height, const char* _name);

	~MyWindow();

	MyWindow(const MyWindow&) = delete;

	MyWindow& operator=(const MyWindow&) = delete;

	void SetTitle(const std::string& _title);

	void EnableCursor() noexcept;

	void DisableCursor() noexcept;

	bool CursorEnabled() const noexcept;

	static std::optional<int> ProcessMessages() noexcept;

public:

	MyMouse mMouse;

	MyKeyboard mKBD;

	Timer mTimer;
private:

	void ConfineCursor() noexcept;

	void FreeCursor() noexcept;

	void ShowCursor() noexcept;

	void HideCursor() noexcept;

	static LRESULT CALLBACK HandleMessageSetup(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

	static LRESULT CALLBACK HandleMessagegThunk(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

	LRESULT HandleMessage(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

private:

	int mWidth, mHeight;

	bool mCursorEnabled = true;

	std::string mCmdLine;

	HWND mHwnd;

	std::vector<BYTE> mRawBuffer;

	// * * Begin Exception Handling * * // 

public:

	class Exception : public MyException

	{
		using MyException::MyException;

	public:

		static std::string TranslateErrorCode(HRESULT _hr);

	};


	class HrException : public Exception
	{
	public:
		HrException(int _line, const char* _file, HRESULT _hr);
		const char* What() const override;
		const char* GetType() const override;
		HRESULT GetErrorCode() const;
		std::string GetErrorDescription() const;
	private:
		HRESULT mHr;
	};

	// * * End Exception Handling * * // 

	// * * Begin Window Class * * //
private:
	class WindowClass {
	public:
		static const char* GetName();
		static HINSTANCE GetInstance();
	private:
		WindowClass();
		WindowClass(const WindowClass&) = delete;
		~WindowClass();
		WindowClass& operator=(const WindowClass&) = delete;

		static constexpr const char* mWndClassName = "My First Game";
		static WindowClass mWndClass;
		HINSTANCE mHInst;
	};

	// * * End Window Class * * //

};

