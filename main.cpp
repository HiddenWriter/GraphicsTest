#include "pch.h"

int CALLBACK WinMain (
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) 
{
	MainWindow wnd(800, 300, "WindowTest");

	MSG msg;
	BOOL gResult = FALSE;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0) > 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (gResult == -1)
	{
		return -1;
	}
	else
	{
		return msg.wParam;
	}
}