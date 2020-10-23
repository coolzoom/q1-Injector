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
	ID_BUTTON_UPDATE,
	ID_BUTTON_SELECT_DLL,
	ID_BUTTON_INJECT,
	ID_TEXT_x32or64
};

struct MainWindow {
	std::wstring NameWindow = L"q1 - Injector";
	int width = 300;
	int height = 350;
	int postX = 0;
	int postY = 0;
};
