#pragma once
#include "Enum_EngineBB.h"
/// 외부 프로젝트와 연결될 EngineBB의 인터페이스들만 모아놓은 .h

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

	/// OnResize
	virtual void OnResize(int width, int height) abstract;

	/// Input(keyboard / mouse) 연결
	virtual void SetInput(std::shared_ptr<__interface IInput>& _input) abstract;
	virtual std::shared_ptr<__interface IInput> GetInput() abstract;

	/// Imgui 핸들 셋팅
	virtual LRESULT ImGuiHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) abstract;
};

__interface IInput
{
public:
	virtual bool Initialize() abstract;
	virtual void Finalize() abstract;

	// 이전 키상태 갱신(Update되기 전 가장먼저 불려야 한다)
	virtual void Update() abstract;
	
	// 입력받기
	virtual void SetKeyboardState(eInput upDown, unsigned char keycode) abstract;
	virtual void SetMousePos(POINT mousePos) abstract;
	virtual void SetMouseRowPos(POINT mouseRowPos) abstract;
	virtual void SetMouseState(eInput upDown, eMouseButtonType mouseType, POINT clickPoint) abstract;
	virtual void SetMouseWheelState(eInput upDown, POINT clickPoint) abstract;

	// 키보드 입력 확인
	virtual bool IsKeyDown(unsigned char keycode) abstract;		// 키가 내려갈 때 한번 true
	virtual bool IsKeyPress(unsigned char keycode) abstract;	// 키를 누르고있을때 항상 true
	virtual bool IsKeyUp(unsigned char keycode) abstract;		// 키가 올라갈때 한번 True
	virtual bool IsKeyRelease(unsigned char keycode) abstract;	// 키를 떼고있을때 항상 True

	// 마우스 위치(실시간)
	virtual POINT GetMousePos() abstract;
	virtual POINT GetMouseRowPos() abstract;

	// 마우스 클릭 위치
	virtual POINT GetClickDownPos() abstract;
	virtual POINT GetClickUpPos() abstract;

	// 마우스 입력 확인
	virtual bool IsDown(eMouseButtonType mouseType) abstract;
	virtual bool IsPress(eMouseButtonType mouseType) abstract;
	virtual bool IsUp(eMouseButtonType mouseType) abstract;
	virtual bool IsRelease(eMouseButtonType mouseType) abstract;

	// 마우스 휠
	virtual bool IsWheelUp() abstract;
	virtual bool IsWheelDown() abstract;
};