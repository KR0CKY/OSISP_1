#include <Windows.h>
#include <tchar.h>

HWND HMainWindow;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");
int APIENTRY _tWinMain(HINSTANCE This, 
	HINSTANCE Prev, 
	LPTSTR cmd, 
	int mode) 
{
	HWND hWnd; 
	MSG msg; 
	WNDCLASS wc; 
	wc.hInstance = This;
	wc.lpszClassName = WinName; 
	wc.lpfnWndProc = WndProc; 
	wc.style = CS_HREDRAW | CS_VREDRAW; 
	wc.hIcon = LoadIcon(NULL, IDI_QUESTION); 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 
	wc.lpszMenuName = NULL; 
	wc.cbClsExtra = 0; 
	wc.cbWndExtra = 0; 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	if (!RegisterClass(&wc)) return 0; 
 
	hWnd = CreateWindow(WinName, 
		_T("osisp_1"), 
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		800, 
		600, 
		HWND_DESKTOP, 
		NULL, 
		This, 
		NULL); 
	ShowWindow(hWnd, mode); 
	HMainWindow = hWnd;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 
		DispatchMessage(&msg); 
	}
	return 0;
}

//parameters for draw
int start_x = 5;
int start_y = 5;
int flag = 1;
int checkUP = 0;
int end_x = 500;
int end_y = 500;
//*******************

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SIZE:
		end_x = LOWORD(lParam);
		end_y = HIWORD(lParam);
		break;
	case WM_LBUTTONDOWN:
		flag = -flag;
		InvalidateRect(HMainWindow, 0, TRUE);
		UpdateWindow(HMainWindow);
		DrawRectangle(HMainWindow, start_x, start_y, flag);
		break;
	case WM_KEYUP:
		checkUP = 0;
		break;
	case WM_MOUSEWHEEL:
		if ((short)HIWORD(wParam) > 0 && !(wParam & MK_SHIFT)) {
			if (start_y > 0)
				start_y -= 2;
			else
				start_y += 2;
			DrawRectangle(HMainWindow, start_x, start_y, flag);
			InvalidateRect(HMainWindow, 0, TRUE);
			UpdateWindow(HMainWindow);
		}
		else if ((short)HIWORD(wParam) < 0 && !(wParam & MK_SHIFT)){
			if (start_y + 50 < end_y)
				start_y += 2;
			else
				start_y -= 2;
			DrawRectangle(HMainWindow, start_x, start_y, flag);
			InvalidateRect(HMainWindow, 0, TRUE);
			UpdateWindow(HMainWindow);
		}
		if ((short)HIWORD(wParam) > 0 && wParam & MK_SHIFT) {
			if (start_x > 0)
				start_x -= 2;
			else
				start_x += 2;
			DrawRectangle(HMainWindow, start_x, start_y, flag);
			InvalidateRect(HMainWindow, 0, TRUE);
			UpdateWindow(HMainWindow);
		}
		else if ((short)HIWORD(wParam) < 0 && wParam & MK_SHIFT) {
			if (start_x + 70 < end_x)
				start_x += 2;
			else
				start_x -= 2;
			DrawRectangle(HMainWindow, start_x, start_y, flag);
			InvalidateRect(HMainWindow, 0, TRUE);
			UpdateWindow(HMainWindow);
		}
		break;
	case WM_KEYDOWN:
		if (wParam == VK_UP) {
			if (checkUP) {
				start_y += 2;
				DrawRectangle(HMainWindow, start_x, start_y, flag);
				InvalidateRect(HMainWindow, 0, TRUE);
				UpdateWindow(HMainWindow);
			}
			else {
				
				start_y -= 2;
				DrawRectangle(HMainWindow, start_x, start_y, flag);
				InvalidateRect(HMainWindow, 0, TRUE);
				UpdateWindow(HMainWindow);
				if (start_y <= 0){
					checkUP = 1;
				}
			}
		}
		if (wParam == VK_DOWN) {
			if (checkUP) {
				start_y -= 2;
				DrawRectangle(HMainWindow, start_x, start_y, flag);
				InvalidateRect(HMainWindow, 0, TRUE);
				UpdateWindow(HMainWindow);
			}
			else {
				start_y += 2;
				DrawRectangle(HMainWindow, start_x, start_y, flag);
				InvalidateRect(HMainWindow, 0, TRUE);
				UpdateWindow(HMainWindow);
				if (start_y + 50 > end_y) {
					checkUP = 1;
				}
			}
		}
		if (wParam == VK_LEFT) {
			if (checkUP) {
				start_x += 2;
				DrawRectangle(HMainWindow, start_x, start_y, flag);
				InvalidateRect(HMainWindow, 0, TRUE);
				UpdateWindow(HMainWindow);
			}
			else {

				start_x -= 2;
				DrawRectangle(HMainWindow, start_x, start_y, flag);
				InvalidateRect(HMainWindow, 0, TRUE);
				UpdateWindow(HMainWindow);
				if (start_x <= 0) {
					checkUP = 1;
				}
			}
		}
		if (wParam == VK_RIGHT) {
			if (checkUP) {
				start_x -= 2;
				DrawRectangle(HMainWindow, start_x, start_y, flag);
				InvalidateRect(HMainWindow, 0, TRUE);
				UpdateWindow(HMainWindow);
			}
			else {
				start_x += 2;
				DrawRectangle(HMainWindow, start_x, start_y, flag);
				InvalidateRect(HMainWindow, 0, TRUE);
				UpdateWindow(HMainWindow);
				if (start_x + 70 > end_x) {
					checkUP = 1;
				}
			}
		}
		break;
	case WM_PAINT:
		DrawRectangle(HMainWindow, start_x, start_y, flag);
		break;
	case WM_DESTROY: PostQuitMessage(0);
		break; 
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void DrawRectangle(HWND hWnd, int x, int y, int _flag) {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	HBRUSH hbrush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, hbrush);
	if (_flag == 1)
		Rectangle(hdc, x, y, x + 100, y + 75);
	else
		Ellipse(hdc, x, y, x + 100, y + 75);
	EndPaint(hWnd, &ps);
}