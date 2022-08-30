#pragma once
#include <queue>
#include <tuple>
#include "Interface_EngineBB.h"

/// <summary>
/// Input(키보드/마우스)를 관리하는 클래스
/// 
/// 2022.08.27 B.Bunny
/// </summary>
class Input : public IInput
{
public:
	Input();
	~Input();

	virtual bool Initialize() override;
	virtual void Finalize() override;
	
	// 이전 키상태 갱신(엔진의 Update안에서 가장나중에 불려야 한다)
	virtual void Update() override;

	// 입력받기
	virtual void SetKeyboardState(eInput upDown, unsigned char keycode) override;
	virtual void SetMousePos(POINT mousePos) override;
	virtual void SetMouseRowPos(POINT mouseRowPos) override;
	virtual void SetMouseState(eInput upDown, eMouseButtonType mouseType, POINT clickPoint) override;
	virtual void SetMouseWheelState(eInput upDown, POINT clickPoint) override;

	// 키보드 입력 확인
	virtual bool IsKeyDown(unsigned char keycode) override;
	virtual bool IsKeyPress(unsigned char keycode) override;
	virtual bool IsKeyUp(unsigned char keycode) override;
	virtual bool IsKeyRelease(unsigned char keycode) override;

	// 마우스 위치(실시간)
	virtual POINT GetMousePos() override;
	virtual POINT GetMouseRowPos() override;

	// 마우스 클릭 위치
	virtual POINT GetClickDownPos() override;
	virtual POINT GetClickUpPos() override;

	// 마우스 입력 확인
	virtual bool IsDown(eMouseButtonType mouseType) override;
	virtual bool IsPress(eMouseButtonType mouseType) override;
	virtual bool IsUp(eMouseButtonType mouseType) override;
	virtual bool IsRelease(eMouseButtonType mouseType) override;
	
	// 마우스 휠
	virtual bool IsWheelUp() override;
	virtual bool IsWheelDown() override;

private:
	std::shared_ptr<class Keyboard> m_spKeyboard;
	std::shared_ptr<class Mouse> m_spMouse;
};

