#pragma once

#include <vector>
#include <Windows.h>

namespace Memory {
	std::vector <std::wstring> GetProcessessName();
	BOOL Inject(wchar_t* pathToDll);
}



namespace Q1 {
	wchar_t* GetPathToDll();
	wchar_t* GetSelectedProcess(HWND hList);
}