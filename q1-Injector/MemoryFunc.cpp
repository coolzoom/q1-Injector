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

BOOL Memory::Inject(wchar_t * pathToDll)
{
	return 0;
}

wchar_t* Q1::GetPathToDll()
{
	OPENFILENAME ofn;
	wchar_t szFile[_MAX_PATH];

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L".dll";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Display the Open dialog box. 

	if (GetOpenFileName(&ofn) == TRUE)
	{
		return szFile;
	}
	return 0;
	
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
