#pragma once

#include <vector>
#include <Windows.h>
#include "q1-Injector.h"


namespace Memory {
	BOOL GetProcessessNameAndPID(std::vector<std::wstring>&processess, std::vector<int>&pIDS);
	BOOL Inject(std::wstring pathToDll, int pID);
}



namespace Q1 {
	BOOL GetPathToDll(std::wstring &pathToDll);
	int GetSelectedProcessAndPID(HWND hList, std::vector<std::wstring> &processess, std::vector<int>& pIDS);
}