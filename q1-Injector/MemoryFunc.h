#pragma once

#include <vector>
#include <Windows.h>
#include "q1-Injector.h"


namespace Memory {
	BOOL GetProcessessNameAndPID(std::vector<std::wstring>&processess, std::vector<int>&pIDS);
	BOOL Inject(wchar_t* pathToDll, int pID);
}



namespace Q1 {
	wchar_t* GetPathToDll();
	int GetSelectedProcessAndPID(HWND hList, std::vector<std::wstring> &processess, std::vector<int>& pIDS);
}