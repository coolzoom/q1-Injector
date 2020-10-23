#pragma once

#include <vector>
#include <Windows.h>

namespace Memory {
	std::vector <std::wstring> GetProcessessName();

	std::wstring GetPathToDll();
	BOOL Inject(std::wstring pathToDll);
}
