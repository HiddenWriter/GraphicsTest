#ifndef PCH_H
#define PCH_H

#define SCREEN_WIDTH 600				//< Window Screen width
#define SECREEN_HEIGHT 800				//< Window Screen height

#include <sdkddkver.h>

#ifndef FULL_WINTARD

#define WIN32_LEAN_AND_MEAN
#define NOGDICAPMASKS
#define NOSYSMETRICS
#define NOMENUS
#define NOICONS
#define NOSYSCOMMANDS
#define NORASTEROPS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOKERNEL
#define NONLS
#define NOMEMMGR
#define NOMETAFILE
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOMINMAX
#define NOTAPE
#endif

#define  _WIN32_WINNT 0x0601

#include <Windows.h>
#include <winerror.h>
#include <iostream>
#include <string>
#include <exception>
#include <queue>
#include <bitset>
#include <sstream>
#include <optional>
#include <chrono>

#include <Windows.h>
#include <d3d11.h>
#include <d3d10.h>
#include <d3dcompiler.h>
#include <wrl.h>

#include "DXErr.h"
#include "Graphics.h"
#include "Timer.h"
#include "MyException.h"
#include "MyMouse.h"
#include "MyKeyboard.h"
#include "MyWindow.h"
#include "TestCode.h"
#include "Application.h"
#include "..\resource.h"



#endif 
// !PCH_H


#ifdef _DEBUG
#ifndef HR
#define HR(x) \
{ \
	HRESULT hr = x;\
	if(FAILED(hr)) \
	{\
		DXTraceW(__FILEW__, __LINE__, hr, L#x, TRUE); \
	}\
}
#endif // HR
#ifndef HR
#define HR(x) x;
#endif
#endif // _DEBUG


