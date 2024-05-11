#include "windows.h"

#define MAX_NAME_SIZE 256
#define HInstance() GetModuleHandle(NULL)

WCHAR windowClass[MAX_NAME_SIZE];
WCHAR windowTitle[MAX_NAME_SIZE];

int windowHeight;
int windowWidth;

int __stdcall WinMain(HINSTANCE, HINSTANCE, PSTR, int) {
	// initialize global variables
	wcscpy_s(windowClass, L"WindowClass");
	wcscpy_s(windowTitle, L"Learning Direct3D 12");
	windowWidth = 800;
	windowHeight = 600;

	// create window class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

	wcex.hIcon = LoadIcon(0, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(0, IDI_APPLICATION);

	wcex.lpszClassName = windowClass;
	wcex.lpszMenuName = nullptr;

	wcex.hInstance = HInstance();

	wcex.lpfnWndProc = DefWindowProc;

	RegisterClassEx(&wcex);

	// create and display window
	HWND hWnd = CreateWindow(windowClass, windowTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, windowWidth, windowHeight, nullptr, nullptr, HInstance(), nullptr);

	if (!hWnd) {
		MessageBox(0, L"Failed to create window...", 0, 0);
		return -1;
	}

	ShowWindow(hWnd, SW_SHOW);

	// listen for message events
	MSG msg = { 0 };
	while (msg.message != WM_QUIT) {
		// if there are window messages then process them
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}