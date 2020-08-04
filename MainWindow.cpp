#include "pch.h"
#include "MainWindow.h"

MainWindow::WindowClass MainWindow::WindowClass::wndClass;

MainWindow::WindowClass::WindowClass() noexcept
	:
	hInst(GetModuleHandle(nullptr)) 
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;	
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = GetName();
	wc.hIconSm = nullptr;

	RegisterClassEx(&wc);

	return;
}

MainWindow::WindowClass::~WindowClass()
{
	UnregisterClass(wndClassName, GetInstance());
	return;
}

const char* MainWindow::WindowClass::GetName() noexcept
{
	return wndClassName;
}

HINSTANCE MainWindow::WindowClass::GetInstance() noexcept
{
	return wndClass.hInst;
}

MainWindow::MainWindow(int width, int height, const char* name) noexcept
{
	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	hWND = CreateWindow(
		WindowClass::GetName(),
		name,
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

	ShowWindow(hWND, SW_SHOWDEFAULT);

	return;
}

MainWindow::~MainWindow()
{
	DestroyWindow(hWND);
	return;
}

LRESULT WINAPI MainWindow::HandleMsgSetup(HWND hWND, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		MainWindow* const pWnd = static_cast<MainWindow*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hWND, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWND, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&MainWindow::HandleMsgThunk));
		return pWnd->HandleMsg(hWND, msg, wParam, lParam);
	}
	return DefWindowProc(hWND, msg, wParam, lParam);
}

LRESULT WINAPI MainWindow::HandleMsgThunk(HWND hWND, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	MainWindow* const pWnd = reinterpret_cast<MainWindow*>(GetWindowLongPtr(hWND, GWLP_USERDATA));
	return pWnd->HandleMsg(hWND, msg, wParam, lParam);
}

LRESULT MainWindow::HandleMsg(HWND hWnd, UINT msg, WPARAM wParm, LPARAM lParam) noexcept
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParm, lParam);
}