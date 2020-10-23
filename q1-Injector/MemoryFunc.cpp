#include "MemoryFunc.h"
#include "q1-Injector.h"

std::vector<char*> Memory::GetProcessessName()
{
	std::vector<char*>processess;
	
	PROCESSENTRY32 pe32{ sizeof(PROCESSENTRY32) };

	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
	if (Process32First(hSnapshot, &pe32))
	{
		do
		{
			//pe32.szExeFile, pe32.th32ProcessID
			
		} while (Process32Next(hSnapshot, &pe32));
	}
	///////

	CloseHandle(hSnapshot);
	return processess;
}
