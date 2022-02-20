#pragma once
#pragma comment(lib, "EngineBB.lib")

#include <string>

class RenderWindow;
class KeyboardClass;
class MouseClass;
class Timer;
class EngineBB;

/// <summary>
/// GameProcess
/// 
/// 2021. 08. 14 B.BUNNY
/// </summary>
class GameProcess
{
public:
	GameProcess();

	bool Initialize(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height);
	void Finalize();
	void Update();

	bool ProcessMessages();
	void Draw();
	
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	EngineBB* m_engineBB;
	RenderWindow* m_Render_window;
	KeyboardClass* m_Keyboard;
	MouseClass* m_Mouse;

private:
	Timer* m_Timer;
	int m_CameraNum = 0;
};