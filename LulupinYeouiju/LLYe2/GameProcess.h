#pragma once
#include <memory>
#include <string>

/// <summary>
/// GameProcess
/// ���� ���� Ŭ����
/// ���ο��� ���� ������ �޽��� �ݹ��� ó���Ѵ�.
/// ���� �׷��Ƚ� ���� ���� �����Ѵ�.
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