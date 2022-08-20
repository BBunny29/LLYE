#pragma once
#include <memory>
#include <string>

/// <summary>
/// GameProcess
/// 게임 진행 클래스
/// 내부에서 윈도 생성과 메시지 콜백을 처리한다.
/// 또한 그래픽스 엔진 등을 포함한다.
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

private:
	std::shared_ptr<class RenderWindow> m_spRenderWindow;
	std::shared_ptr<__interface IEngineBB> m_spEngineBB;
	std::shared_ptr<__interface ITest> m_spTest;

private:
	int m_CameraNum = 0;
};