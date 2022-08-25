#pragma once
/// <summary>
/// 엔진의 인터페이스(껍데기)
/// 바깥부분(게임 프로젝트)에서 사용할 함수들만 가상함수로 만든다.
/// 
/// 2022.08.21 B.Bunny
/// </summary>
__interface IEngineBB
{
public:
	virtual bool Initialize(int hWND, int width, int height) abstract;
	virtual bool Loop() abstract;
	virtual void Finalize() abstract;

	virtual void SetKeyInput(std::shared_ptr<__interface ITestOutClass>& testOutClass) abstract;
	virtual std::shared_ptr<__interface ITestOutClass> GetKeyInput(unsigned char keycode) abstract;


	virtual LRESULT ImGuiHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) abstract;
};