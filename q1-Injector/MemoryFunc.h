#pragma once

#include <vector>
#include <Windows.h>


namespace Memory {
	BOOL GetProcessessNameAndPID(std::vector<std::wstring>&processess, std::vector<int>&pIDS);
	BOOL Inject(wchar_t* pathToDll);
}



namespace Q1 {
	wchar_t* GetPathToDll();
	wchar_t* GetSelectedProcess(HWND hList);
}