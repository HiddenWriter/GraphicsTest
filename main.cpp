#include "pch.h"

tagMSG msg = { 0 };
BOOL gResult = FALSE;

int WINAPI WinMain
(
	HINSTANCE _hIns,
	HINSTANCE _prevIns,
	LPSTR _lpCmdLine,
	int _nShowCmd
)
{
	
	try
	{
		Application{ _lpCmdLine }.Go();
	}
	catch (const MyException & e)
	{
		MessageBox(nullptr, e.What(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception e)
	{
		MessageBox(nullptr, e.what(), "STANDARD EXCEPTION", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "NO DETAILS AVAILABLE", "UNKNOWN EXCEPTION", MB_OK | MB_ICONEXCLAMATION);
	}
	
	return -1;
}
