#pragma once
#include <memory>
#include <string>


__interface IEngineBB;
template<typename T> class DLLImporter;

class RenderWindow;

/// <summary>
/// GameProcess
/// 
/// 2021. 08. 14 B.BUNNY
/// </summary>
class GameProcess
{
public:
	GameProcess();
	~GameProcess();

	bool Initialize(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height);
	void Finalize();
	void Update();

	bool ProcessMessages();
	void Draw();
	
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	std::shared_ptr<IEngineBB> CreateEngine(const wchar_t* dllPath);

private:
	

	std::shared_ptr<RenderWindow> m_spRenderWindow;
	std::shared_ptr<IEngineBB> m_spEngineBB;
	//KeyboardClass* m_Keyboard;
	//MouseClass* m_Mouse;

private:
	int m_CameraNum = 0;
};