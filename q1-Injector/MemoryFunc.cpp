#include "MemoryFunc.h"
#include "q1-Injector.h"

std::vector<std::wstring> Memory::GetProcessessName()
{
	std::vector<std::wstring>processess;
	
	PROCESSENTRY32 pe32{ sizeof(PROCESSENTRY32) };

	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
	if (Process32First(hSnapshot, &pe32))
	{
		do
		{
			processess.push_back(pe32.szExeFile);
			
		} while (Process32Next(hSnapshot, &pe32));
	}


	CloseHandle(hSnapshot);
	return processess;
}

std::wstring Q1::GetPathToDll()
{

	return std::wstring();
}

wchar_t* Q1::GetSelectedProcess(HWND hList)
{
	auto i = SendMessage(hList, LB_GETCURSEL, 0, 0);
	if (i != LB_ERR)
	{
		wchar_t Temp[_MAX_DIR];
		SendMessage(hList, LB_GETTEXT, i, (LPARAM)Temp);
		return Temp;
	}
	return 0;
}
