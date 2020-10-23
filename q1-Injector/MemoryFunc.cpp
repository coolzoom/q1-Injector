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
