#pragma once

#include "MemoryFunc.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <string>

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

int __stdcall wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow);
LRESULT __stdcall WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

enum ID_ {
	ID_LIST,
	ID_BUTTON
};

struct MainWindow {
	int width = 300;
	int height = 350;
	int postX = 0;
	int postY = 0;
};
