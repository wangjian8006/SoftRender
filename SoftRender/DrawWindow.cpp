#include "DrawWindow.h"

bool DrawWindow::WINDOW_CLOSE = false;
int DrawWindow::KEYS[512] = {0};		//¼üÅÌ×´Ì¬

static LRESULT WindowEvents(HWND hWnd, 
						UINT msg, 
						WPARAM wParam, 
						LPARAM lParam)
{
	switch (msg)
	{
		case WM_KEYDOWN: DrawWindow::KEYS[wParam & 511] = 1; break;
		case WM_KEYUP: DrawWindow::KEYS[wParam & 511] = 0; break;
		case WM_CLOSE: DrawWindow::WINDOW_CLOSE = true;
		default: return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

DrawWindow::DrawWindow(DrawDevice* device)
{
	this->m_device = device;
}

bool DrawWindow::CheckClose()
{
	return KEYS[VK_ESCAPE] || WINDOW_CLOSE == true;
}

int DrawWindow::InitWindow(int w, int h, const TCHAR *title)
{
	this->m_iWidth = w;
	this->m_iHeight = h;

	WNDCLASS wc = { CS_BYTEALIGNCLIENT, (WNDPROC)WindowEvents, 0, 0, 0, 
		NULL, NULL, NULL, NULL, _T("SCREEN3.1415926") };
	BITMAPINFO bi = { { sizeof(BITMAPINFOHEADER), w, -h, 1, 32, BI_RGB, 
		w * h * 4, 0, 0, 0, 0 }  };
	RECT rect = { 0, 0, w, h };
	LPVOID ptr;

	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hInstance = GetModuleHandle(NULL);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	if (!RegisterClass(&wc)) return -1;

	this->m_hwnd = CreateWindow(_T("SCREEN3.1415926"), title,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 0, 0, 0, NULL, NULL, wc.hInstance, NULL);
	if (this->m_hwnd == NULL) return -2;

	//screen_exit = 0;
	HDC hDC = GetDC(this->m_hwnd);
	this->m_hdc = CreateCompatibleDC(hDC);
	ReleaseDC(this->m_hwnd, hDC);

	m_ScreenDIB = CreateDIBSection(this->m_hdc, &bi, DIB_RGB_COLORS, &ptr, 0, 0);
	if (m_ScreenDIB == NULL) return -3;
	
	m_ScreenOldDIB = (HBITMAP)SelectObject(this->m_hdc, m_ScreenDIB);
	this->m_device->SetFrameBuffer(ptr);
	
	AdjustWindowRect(&rect, GetWindowLong(this->m_hwnd, GWL_STYLE), 0);
	int wx = rect.right - rect.left;
	int wy = rect.bottom - rect.top;
	int sx = (GetSystemMetrics(SM_CXSCREEN) - wx) / 2;
	int sy = (GetSystemMetrics(SM_CYSCREEN) - wy) / 2;
	if (sy < 0) sy = 0;
	SetWindowPos(this->m_hwnd, NULL, sx, sy, wx, wy, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));
	SetForegroundWindow(this->m_hwnd);

	ShowWindow(this->m_hwnd, SW_NORMAL);
	this->WindowMessageDispatch();

	memset(ptr, 0, w * h * 4);

	return 0;
}

void DrawWindow::WindowUpdate(void)
{
	HDC hDC = GetDC(this->m_hwnd);
	BitBlt(hDC, 0, 0, this->m_iWidth, this->m_iHeight, this->m_hdc, 0, 0, SRCCOPY);
	ReleaseDC(this->m_hwnd, hDC);
	this->WindowMessageDispatch();
}

void DrawWindow::WindowMessageDispatch()
{
	MSG msg;
	while (1) {
		if (!PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) break;
		if (!GetMessage(&msg, NULL, 0, 0)) break;
		DispatchMessage(&msg);
	}
}