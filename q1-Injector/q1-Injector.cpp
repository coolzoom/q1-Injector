#include "q1-Injector.h"
#include "MemoryFunc.h"

HWND hList;
HWND hButtonUpd;
HWND hButtonInject;
HWND hButtonSelect;
HINSTANCE hInst;
MainWindow windowParams;
std::wstring pathToDll;
BOOL pathToDllResult = FALSE;

std::vector<std::wstring>processess;
std::vector<int>pIDS;

int __stdcall wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

	hInst = hInstance;
	MSG msg = { };
	WNDCLASS wc = { };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(230));
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = L"q1_Injector";
	wc.lpszMenuName = nullptr;
	wc.style = CS_HREDRAW | CS_VREDRAW;


	RegisterClass(&wc);
	HWND hwnd = CreateWindowEx(
			NULL, wc.lpszClassName, windowParams.NameWindow.c_str(), 
			WS_OVERLAPPEDWINDOW,
			windowParams.postX, windowParams.postY, windowParams.width, windowParams.height,
			NULL, nullptr, hInstance, NULL);

	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT __stdcall WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CREATE:
		{
			//BUTTON
			hButtonUpd = CreateWindow(L"button", L"UPDATE", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, (windowParams.width / 2) + 5, 0, (windowParams.width / 2) - 25, (windowParams.height / 3) - 20, hwnd, reinterpret_cast<HMENU>(ID_::ID_BUTTON_UPDATE), hInst, NULL);
			hButtonSelect = CreateWindow(L"button", L"SELECT", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, (windowParams.width / 2) + 5, (windowParams.height / 3) - 20, (windowParams.width / 2) - 25, (windowParams.height / 3) - 20, hwnd, reinterpret_cast<HMENU>(ID_::ID_BUTTON_SELECT_DLL), hInst, NULL);
			hButtonInject = CreateWindow(L"button", L"INJECT", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, (windowParams.width / 2) + 5, ((windowParams.height / 3) - 20) + (windowParams.height / 3) - 20, (windowParams.width / 2) - 25, (windowParams.height / 3) - 20, hwnd, reinterpret_cast<HMENU>(ID_::ID_BUTTON_INJECT), hInst, NULL);
			//LISTBOX
			hList = CreateWindow(L"listbox", NULL, WS_CHILD | WS_VISIBLE | LBS_STANDARD, 0, 0, windowParams.width / 2, windowParams.height - 35, hwnd, reinterpret_cast<HMENU>(ID_::ID_LIST), hInst, NULL);
			//LABEL
			CreateWindow(L"STATIC", L"x32", WS_VISIBLE | WS_CHILD, ((windowParams.width / 2) + 5), ((((windowParams.height / 3) - 20) + (windowParams.height / 3) - 20) + windowParams.height / 3) - 20, 25, 18, hwnd, reinterpret_cast<HMENU>(ID_::ID_TEXT_x32or64), hInst, NULL);
			

			Memory::GetProcessessNameAndPID(processess, pIDS);
			unsigned int index = 0;
			for (auto process : processess)
			{
				std::wstring processAndPid = (std::wstring)(L"[") + std::to_wstring(pIDS[index]) + (std::wstring)(L"]") + processess[index];
				SendMessage(hList, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(processAndPid.c_str()));
				index++;
			}
		}
		return 0;

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{

				case ID_::ID_BUTTON_UPDATE:
				{
					
					ZeroMemory(&processess, sizeof(std::vector<std::wstring>));
					ZeroMemory(&pIDS, sizeof(std::vector<int>));
					SendMessage(hList, LB_RESETCONTENT, 0, 0);
					Memory::GetProcessessNameAndPID(processess, pIDS);
					
					unsigned int index = 0;
					for (auto process : processess)
					{
						std::wstring processAndPid = (std::wstring)(L"[") + std::to_wstring(pIDS[index]) + (std::wstring)(L"]") + processess[index];
						SendMessage(hList, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(processAndPid.c_str()));
						index++;
					}
						
				}
				break;
			
				case ID_::ID_BUTTON_SELECT_DLL:
				{
					pathToDllResult = Q1::GetPathToDll(pathToDll);
				}
				break;

				case ID_::ID_BUTTON_INJECT:
				{
					int pID = Q1::GetSelectedProcessAndPID(hList, processess, pIDS);
					if (pID == 0)
					{
						MessageBox(NULL, L"No process selected", L"Error", MB_ICONERROR);
						break;
					}

					if (!pathToDllResult)
					{
						MessageBox(NULL, L"Dll not selected", L"Error", MB_ICONERROR);
						break;
					}

					if (!Memory::Inject(pathToDll, pID)) 
					{
						MessageBox(NULL, L"Dll was not injected", L"Error", MB_ICONERROR);
						break;
					}

				}
				break;
			}
			return 0;
		}
		return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
