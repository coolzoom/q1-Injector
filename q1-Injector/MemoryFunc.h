#pragma once

#include <vector>
#include <Windows.h>

namespace Memory {
	std::vector <std::wstring> GetProcessessName();
	BOOL Inject(std::wstring pathToDll);
}



namespace Q1 {
	std::wstring GetPathToDll();
	wchar_t* GetSelectedProcess(HWND hList);

}