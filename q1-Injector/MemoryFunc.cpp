#include "MemoryFunc.h"
#include "q1-Injector.h"



BOOL Memory::GetProcessessNameAndPID(std::vector<std::wstring>&processess, std::vector<int>&pIDS)
{
	PROCESSENTRY32 pe32{ sizeof(PROCESSENTRY32) };

	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
	if (Process32First(hSnapshot, &pe32))
	{
		do
		{
			processess.push_back(pe32.szExeFile);
			pIDS.push_back(pe32.th32ProcessID);
		} while (Process32Next(hSnapshot, &pe32));
	}

	CloseHandle(hSnapshot);
	return true;
}

BOOL Memory::Inject(std::wstring dllPath, int pID)
{
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pID);
	if (!hProcess)
		return FALSE;

	LPVOID mem_allocation = VirtualAllocEx(hProcess, NULL, dllPath.size() + 1, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (!mem_allocation)
		return FALSE;

	if (WriteProcessMemory(hProcess, mem_allocation, dllPath.c_str(), dllPath.size() * 2, 0) <= 0)
		return FALSE;

	DWORD dummy;
	HANDLE RemThread = CreateRemoteThread(hProcess, NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(GetProcAddress(LoadLibrary(L"kernel32"), "LoadLibraryW")), mem_allocation, 0, &dummy);

	if (!RemThread) return FALSE;

	CloseHandle(RemThread);
	CloseHandle(hProcess);
	return true;
}

BOOL Q1::GetPathToDll(std::wstring &pathToDll)
{
	OPENFILENAME ofn;
	wchar_t szFile[_MAX_PATH];

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"Dll files(*.dll)\0*.dll";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		pathToDll = szFile;
		return 	TRUE;
	}
	return FALSE;
	
}

int Q1::GetSelectedProcessAndPID(HWND hList, std::vector<std::wstring> &processess, std::vector<int>& pIDS)
{
	auto i = SendMessage(hList, LB_GETCURSEL, 0, 0);
	if (i != LB_ERR)
	{
		wchar_t Temp[_MAX_DIR];
		SendMessage(hList, LB_GETTEXT, i, (LPARAM)Temp);

		unsigned int index = 0;
		for (auto process : processess)
		{
			std::wstring processAndPid = (std::wstring)(L"[") + std::to_wstring(pIDS[index]) + (std::wstring)(L"]") + processess[index];
			std::wstring ws(Temp);

			if (wcscmp(processAndPid.c_str(), Temp) == 0) return pIDS[index];
			index++;
		}
	}
	return 0;
}
