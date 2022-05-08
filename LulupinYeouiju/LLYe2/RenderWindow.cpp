#include "pch.h"
#include "RenderWindow.h"

#include "GameProcess.h"
#include "ErrorLogger.h"
#include "StringHelper.h"

RenderWindow::RenderWindow()
{
}

RenderWindow::~RenderWindow()
{
	if (this->m_handle != NULL)
	{
		UnregisterClass(m_window_class_wide.c_str(), m_hInstance);
		DestroyWindow(m_handle);
	}
}

bool RenderWindow::Initialize(GameProcess* gameProcess, HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height)
{
	m_hInstance = hInstance;
	
	m_window_title = window_title;
	m_window_title_wide = StringHelper::StringToWString(m_window_title);
	m_window_class = window_class;
	m_window_class_wide = StringHelper::StringToWString(m_window_class); //wide string representation of class string (used for registering class and creating window)
	
	m_width = width;
	m_height = height;

	RegisterWindowClass();

	int centerScreenX = GetSystemMetrics(SM_CXSCREEN) / 2 - m_width / 2;
	int centerScreenY = GetSystemMetrics(SM_CYSCREEN) / 2 - m_height / 2;

	RECT wr;
	wr.left = centerScreenX;
	wr.top = centerScreenY;
	wr.right = wr.left + this->m_width;
	wr.bottom = wr.top + this->m_height;

	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	/// <summary>
	/// 핸들 생성
	/// </summary>
	/// <param name="gameProcess"></param>
	/// <param name="hInstance"></param>
	/// <param name="window_title"></param>
	/// <param name="window_class"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <returns></returns>
	m_handle = CreateWindowEx(0, //Extended Windows style - we are using the default. For other options, see: https://msdn.microsoft.com/en-us/library/windows/desktop/ff700543(v=vs.85).aspx
		m_window_class_wide.c_str(), //Window class name
		m_window_title_wide.c_str(), //Window Title
		WS_OVERLAPPEDWINDOW,//WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, //Windows style - See: https://msdn.microsoft.com/en-us/library/windows/desktop/ms632600(v=vs.85).aspx
		wr.left, //Window X Position
		wr.top, //Window Y Position
		wr.right - wr.left, //Window Width
		wr.bottom - wr.top, //Window Height
		NULL, //Handle to parent of this window. Since this is the first window, it has no parent window.
		NULL, //Handle to menu or child window identifier. Can be set to NULL and use menu in WindowClassEx if a menu is desired to be used.
		m_hInstance, //Handle to the instance of module to be used with this window
		gameProcess); //Param to create window

	if (m_handle == NULL)
	{
		ErrorLogger::Log(GetLastError(), "CreateWindowEX Failed for window: " + this->m_window_title);
		return false;
	}

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_handle, SW_SHOW);
	SetForegroundWindow(m_handle);
	SetFocus(m_handle);

	return true;
}

void RenderWindow::Finalize()
{
}

bool RenderWindow::ProcessMessages()
{
	// Handle the windows messages.
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG)); // Initialize the message structure.

	while (PeekMessage(&msg, //Where to store message (if one exists) See: https://msdn.microsoft.com/en-us/library/windows/desktop/ms644943(v=vs.85).aspx
		m_handle, //Handle to window we are checking messages for
		0,    //Minimum Filter Msg Value - We are not filtering for specific messages, but the min/max could be used to filter only mouse messages for example.
		0,    //Maximum Filter Msg Value
		PM_REMOVE))//Remove message after capturing it via PeekMessage. For more argument options, see: https://msdn.microsoft.com/en-us/library/windows/desktop/ms644943(v=vs.85).aspx
	{
		TranslateMessage(&msg); //Translate message from virtual key messages into character messages so we can dispatch the message. See: https://msdn.microsoft.com/en-us/library/windows/desktop/ms644955(v=vs.85).aspx
		DispatchMessage(&msg); //Dispatch message to our Window Proc for this window. See: https://msdn.microsoft.com/en-us/library/windows/desktop/ms644934(v=vs.85).aspx
	}

	// Check if the window was closed
	if (msg.message == WM_NULL)
	{
		if (!IsWindow(m_handle))
		{
			m_handle = NULL; //Message processing loop takes care of destroying this window
			UnregisterClass(m_window_class_wide.c_str(), m_hInstance);
			return false;
		}
	}

	return true;
}

HWND RenderWindow::GetHWND() const
{
	return m_handle;
}

LRESULT CALLBACK HandleMsgRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		// All other messages
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;

	default:
	{
		// retrieve ptr to window class
		GameProcess* const pWindow = reinterpret_cast<GameProcess*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		// forward message to window class handler
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
	}
}

LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_NCCREATE:
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		GameProcess* pWindow = reinterpret_cast<GameProcess*>(pCreate->lpCreateParams);
		if (pWindow == nullptr) //Sanity check
		{
			//ErrorLogger::Log("Critical Error: Pointer to window container is null during WM_NCCREATE.");
			exit(-1);
		}
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgRedirect));
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

/// <summary>
/// 
/// </summary>
void RenderWindow::RegisterWindowClass()
{
	WNDCLASSEX wc; //Our Window Class (This has to be filled before our window can be created) See: https://msdn.microsoft.com/en-us/library/windows/desktop/ms633577(v=vs.85).aspx
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; //Flags [Redraw on width/height change from resize/movement] See: https://msdn.microsoft.com/en-us/library/windows/desktop/ff729176(v=vs.85).aspx
	wc.lpfnWndProc = HandleMessageSetup; //Pointer to Window Proc function for handling messages from this window
	wc.cbClsExtra = 0; //# of extra bytes to allocate following the window-class structure. We are not currently using this.
	wc.cbWndExtra = 0; //# of extra bytes to allocate following the window instance. We are not currently using this.
	wc.hInstance = m_hInstance; //Handle to the instance that contains the Window Procedure
	wc.hIcon = NULL;   //Handle to the class icon. Must be a handle to an icon resource. We are not currently assigning an icon, so this is null.
	wc.hIconSm = NULL; //Handle to small icon for this class. We are not currently assigning an icon, so this is null.
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //Default Cursor - If we leave this null, we have to explicitly set the cursor's shape each time it enters the window.
	wc.hbrBackground = NULL; //Handle to the class background brush for the window's background color - we will leave this blank for now and later set this to black. For stock brushes, see: https://msdn.microsoft.com/en-us/library/windows/desktop/dd144925(v=vs.85).aspx
	wc.lpszMenuName = NULL; //Pointer to a null terminated character string for the menu. We are not using a menu yet, so this will be NULL.
	wc.lpszClassName = m_window_class_wide.c_str(); //Pointer to null terminated string of our class name for this window.
	wc.cbSize = sizeof(WNDCLASSEX); //Need to fill in the size of our struct for cbSize
	
	RegisterClassEx(&wc); // Register the class so that it is usable.
}