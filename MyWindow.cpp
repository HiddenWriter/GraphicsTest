#include "pch.h"
#include "MyWindow.h"

// Window 

MyWindow::MyWindow(int _width, int _height, const char* _name)
	:
	mWidth(_width), mHeight(_height)
{
	// Calculate window size based upon desired client region size
	RECT wr;
	wr.left = 100;
	wr.right = mWidth + wr.left;
	wr.top = 100;
	wr.bottom = mHeight + wr.top;
	
	AdjustWindowRectEx(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE, NULL);

	mHwnd = CreateWindowExA
	(
		NULL,
		WindowClass::GetName(),
		_name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wr.right - wr.left,
		wr.bottom - wr.top,
		nullptr,
		nullptr,
		WindowClass::GetInstance(),
		this
	);
	ShowWindow(mHwnd, SW_SHOWDEFAULT);
	return;
}

MyWindow::~MyWindow()
{
	DestroyWindow(mHwnd);
	return;
}

// Window Class

void MyWindow::SetTitle(const std::string& _title)
{
	if (SetWindowText(mHwnd, _title.c_str()) == 0)
	{
		std::abort();
	}
}

void MyWindow::EnableCursor() noexcept
{
	mCursorEnabled = true;
	ShowCursor();
	FreeCursor();
	return;
}

void MyWindow::DisableCursor() noexcept
{
	mCursorEnabled = false;
	HideCursor();
	ConfineCursor();
	return;
}

bool MyWindow::CursorEnabled() const noexcept
{
	return mCursorEnabled;
}

std::optional<int> MyWindow::ProcessMessages() noexcept
{
	MSG msg;
	while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return (int)msg.wParam;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return {};
}

void MyWindow::FreeCursor() noexcept
{
	ClipCursor(nullptr);
	return;
}

void MyWindow::ConfineCursor() noexcept
{
	RECT rect;
	GetClientRect(mHwnd, &rect);
	MapWindowPoints(mHwnd, nullptr, reinterpret_cast<POINT*>(&rect), 2);
	ClipCursor(&rect);
	return;
}

void MyWindow::HideCursor() noexcept
{
	while (::ShowCursor(FALSE) >= 0);

	return;
}

void MyWindow::ShowCursor() noexcept
{
	while (::ShowCursor(TRUE) < 0);
	return;
}


MyWindow::WindowClass MyWindow::WindowClass::mWndClass;

MyWindow::WindowClass::WindowClass() 
	:
	mHInst(GetModuleHandle(nullptr))
{
	WNDCLASSEXA wc = { 0 };

	SecureZeroMemory(&wc, sizeof(WNDCLASSEXA));

	wc.cbSize = sizeof(WNDCLASSEXA);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMessageSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();
	wc.hIcon = static_cast<HICON>(LoadImage(GetInstance(), MAKEINTRESOURCE(101), IMAGE_ICON, 32, 32, 0));
	wc.hIconSm = static_cast<HICON>(LoadImage(GetInstance(), MAKEINTRESOURCE(101), IMAGE_ICON, 16, 16, 0));
	wc.hCursor = static_cast<HCURSOR>(LoadCursor(GetInstance(), MAKEINTRESOURCE(103)));
	wc.hbrBackground = nullptr;
	wc.lpszClassName = GetName();
	wc.lpszMenuName = nullptr;
	
	RegisterClassExA(&wc);

	return;
}

MyWindow::WindowClass::~WindowClass()
{
	UnregisterClass(GetName(), GetInstance());
	return;
}

const char* MyWindow::WindowClass::GetName() 
{
	return mWndClassName;
}

HINSTANCE MyWindow::WindowClass::GetInstance() 
{
	return mWndClass.mHInst;
}

		// * * Begin CALLBACK * * //

LRESULT CALLBACK MyWindow::HandleMessageSetup(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam) 
{
	if (_msg == WM_NCCREATE)
	{
		
		// Extract ptr to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(_lParam);
		MyWindow* const pWnd = static_cast<MyWindow*>(pCreate->lpCreateParams);

		// Set WinAPI-managed user data to store ptr to window instance
		SetWindowLongPtr(_hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));

		// Set winodw procedure to normal handler now that setup is finished 
		SetWindowLongPtr(_hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&MyWindow::HandleMessagegThunk));

		return pWnd->HandleMessage(_hWnd, _msg, _wParam, _lParam);
	}
	return DefWindowProc(_hWnd, _msg, _wParam, _lParam);
}

LRESULT CALLBACK MyWindow::HandleMessagegThunk(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam) 
{
	// Retrieve ptr to window instance 
	MyWindow* const pWnd = reinterpret_cast<MyWindow*>(GetWindowLongPtr(_hWnd, GWLP_USERDATA));

	// Forward message to the window instance handler
	return pWnd->HandleMessage(_hWnd, _msg, _wParam, _lParam);
}

LRESULT MyWindow::HandleMessage(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam) 
{
	switch (_msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;

	case WM_KILLFOCUS:
		mKBD.ClearState();
		break;

	case WM_ACTIVATE:
	{
		if (!mCursorEnabled)
		{
			if (_wParam & WA_ACTIVE)
			{
				ConfineCursor();
				HideCursor();
			}
			else
			{
				FreeCursor();
				ShowCursor();
			}
		}
		break;

	}
	// Begin Keyboard Messages

	case WM_KEYDOWN:
		break;
	case WM_KEYUP:
		break;
	case WM_SYSKEYDOWN:
	{
		if (!(_wParam & 0x40000000 || mKBD.AutoRepeatIsEnabled()))
		{
			mKBD.OnKeyPressed(static_cast<unsigned char>(_wParam));
		}
		break;

	}
	case WM_SYSKEYUP:
		mKBD.OnKeyReleased(static_cast<unsigned char>(_wParam));
		break;
	case WM_CHAR:
	{
		mKBD.OnChar(static_cast<unsigned char>(_wParam));
		break;
	}

	// End Keyboard Messages 

	// Begin Mouse Messages
	case WM_MOUSEMOVE:
	{
		const POINTS pt = MAKEPOINTS(_lParam);

		if (!mCursorEnabled)
		{
			if (!mMouse.IsInWindow())
			{
				SetCapture(mHwnd);
				mMouse.OnMouseEnter();
				HideCursor();
			}
			break;
		}
		if (pt.x >= 0 && pt.x < mWidth && pt.y >= 0 && pt.y < mHeight)
		{
			mMouse.OnMouseMove(pt.x, pt.y);
			if (!mMouse.IsInWindow())
			{
				SetCapture(mHwnd);
				mMouse.OnMouseEnter();
			}
		}
		else
		{
			if ( mMouse.LeftIsPressed() & (MK_LBUTTON | MK_RBUTTON))
			{
				mMouse.OnMouseMove(pt.x, pt.y);
			}
			else
			{
				ReleaseCapture();
				mMouse.OnMouseLeave();
			}
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		SetForegroundWindow(mHwnd);
		if (!mCursorEnabled)
		{
			ConfineCursor();
			HideCursor();
		}
		const POINTS pt = MAKEPOINTS(_lParam);
		mMouse.OnLeftIsPressed(pt.x, pt.y);
		break;
	}
	case WM_LBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(_lParam);
		mMouse.OnLeftIsReleased(pt.x, pt.y);

		if (pt.x < 0 || pt.x >= mWidth || pt.y < 0 || pt.y >= mHeight)
		{
			ReleaseCapture();
			mMouse.OnMouseLeave();
		}
		break;
	}
	case WM_RBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(_lParam);
		mMouse.OnRightIsPressed(pt.x, pt.y);
		break;
	}

	case WM_RBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(_lParam);
		mMouse.OnRightIsReleased(pt.x, pt.y);

		if (pt.x < 0 || pt.x >= mWidth || pt.y < 0 || pt.y >= mHeight)
		{
			ReleaseCapture();
			mMouse.OnMouseLeave();
		}
		break;
	}
	case WM_MOUSEWHEEL:
	{
		const POINTS pt = MAKEPOINTS(_lParam);
		const int delta = GET_WHEEL_DELTA_WPARAM(_wParam);
		mMouse.OnWheelDelta(pt.x, pt.y, delta);
		break;
	}

	// End Mouse Messages

	// Begin Raw Mouse Messages

	case WM_INPUT:
	{
		if (!mMouse.RawEnabled()) break;
		UINT size;

		if (GetRawInputData(
			reinterpret_cast<HRAWINPUT>(_lParam),
			RID_INPUT,
			nullptr,
			&size,
			sizeof(RAWINPUTHEADER)
		)
			== -1
			)
		{
			break;
		}
		mRawBuffer.resize(size);

		if (GetRawInputData(
			reinterpret_cast<HRAWINPUT>(_lParam),
			RID_INPUT,
			mRawBuffer.data(),
			&size,
			sizeof(RAWINPUTHEADER)
		)
			!= size
			)
		{
			break;
		}

		auto& ri = reinterpret_cast<const RAWINPUT&>(*mRawBuffer.data());
		if (ri.header.dwType == RIM_TYPEMOUSE &&
			(ri.data.mouse.lLastX != 0 || ri.data.mouse.lLastY != 0))
		{
			mMouse.OnRawDelta(ri.data.mouse.lLastX, ri.data.mouse.lLastY);
		}
		break;
	}
	}
	return DefWindowProc(_hWnd, _msg, _wParam, _lParam);
}

		// * * End CALLBACK * * //
		
		// * * Begin Exception Handling * * // 

std::string MyWindow::Exception::TranslateErrorCode(HRESULT _hr) 
{
	char* pMsgBuffer = nullptr;

	const DWORD nMsgLen = FormatMessage
	(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,

		nullptr,
		_hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&pMsgBuffer),
		0,
		nullptr
	);

	if (nMsgLen == 0)
	{
		return "\n\t Unidentified Error \n";
	}

	std::string errorString = pMsgBuffer;

	LocalFree(pMsgBuffer);

	return errorString;
}

MyWindow::HrException::HrException(int _line, const char* _file, HRESULT _hr)
	:
	Exception(_line, _file),
	mHr(_hr)
{
	return;
}

const char* MyWindow::HrException::What() const 
{
	std::ostringstream oss;
	oss << GetType() << "\n"
		<< "\n\t ERROR CODE 0x " << std::hex << std::uppercase << GetErrorCode()
		<< std::dec << " (" << (unsigned long)GetErrorCode() << ")" << "\n"
		<< "\n\t Description" << GetErrorDescription() << "\n"
		<< GetOriginString();

	mWhatBuffer = oss.str();
	return mWhatBuffer.c_str();
}

const char* MyWindow::HrException::GetType() const
{
	return "\n\t My Exception \n";
}

HRESULT MyWindow::HrException::GetErrorCode() const
{
	return mHr;
}

std::string MyWindow::HrException::GetErrorDescription() const
{
	return Exception::TranslateErrorCode(mHr);
}

		// * * End Exception Handling * * // 