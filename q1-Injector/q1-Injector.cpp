#include "q1-Injector.h"

int __stdcall wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {


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
				NULL, wc.lpszClassName, L"q1 - Injector", 
				WS_OVERLAPPEDWINDOW,
				0, 0, 250, 350, 
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
		HWND hList = CreateWindow(L"listbox", NULL, WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_NOTIFY,
			30, 30, 200, 100, hWnd, (HMENU)ID_LIST, hInst, NULL);

	}
	return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
