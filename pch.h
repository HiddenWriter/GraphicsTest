#ifndef PCH_H
#define PCH_H

#define SCREEN_WIDTH 600				//< Window Screen width
#define SECREEN_HEIGHT 800				//< Window Screen height

#define  _WIN32_WINNT 0x0601
#define NOMINMAX

#include <Windows.h>
#include <iostream>>
#include <string>
#include <exception>
#include <queue>
#include <bitset>
#include <sstream>
#include <optional>
#include <chrono>

#include "Timer.h"
#include "MyException.h"
#include "MyMouse.h"
#include "MyKeyboard.h"
#include "MyWindow.h"
#include "TestCode.h"
#include "Application.h"
#include "resource.h"

#define HWND_LAST_EXCEPT() MyWindow::Exception(__LINE__, __FILE__, GetLastError())
#endif // !PCH_H
