#pragma once

#define WINDOWS_EXCEPT(hr) MyWindow::HrException(__LINE__, __FILE__, (hr))
#define WINDOWS_LAST_EXCEPT() MyWindow::HrException(__LINE__, __FILE__, GetLastError())
#define WINDOWS_NOGFX_EXCEPT() MyWindow::NoGfxException(__LINE__, __FILE__)
