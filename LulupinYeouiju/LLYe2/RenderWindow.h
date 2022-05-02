#pragma once
#include <string>

class GameProcess;

class RenderWindow
{
public:
	RenderWindow();
	~RenderWindow();

	bool Initialize(GameProcess* gameProcess, HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height);
	void Finalize();
	bool ProcessMessages();
	HWND GetHWND() const;

private:
	void RegisterWindowClass();

private:
	HWND m_handle = nullptr;			//Handle to this window
	HINSTANCE m_hInstance = nullptr;	//Handle to application instance
	
	std::string window_title = "";
	std::wstring window_title_wide = L""; //Wide string representation of window title
	std::string window_class = "";
	std::wstring window_class_wide = L""; //Wide string representation of window class name

	int m_width = 0;
	int m_height = 0;
};