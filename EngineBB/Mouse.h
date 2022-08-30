#pragma once
#include <queue>
#include "Enum_EngineBB.h"

class Mouse
{
public:
	Mouse();
	~Mouse();

	// 현재 마우스버튼 상태를 이전상태로 옮긴다
	void UpdateMouse();

	// 마우스 이동 포지션 받는 함수
	void OnMouseMove(POINT mousePos);
	void OnMouseMoveRaw(POINT mouseRowPos);
	
	// 마우스버튼 상태를 설정하는 함수
	void OnButtonDown(eMouseButtonType buttonType, POINT clickPoint);
	void OnButtonUp(eMouseButtonType buttonType, POINT clickPoint);

	// 마우스휠 상태를 설정받는 함수
	void OnWheelUp(POINT mousePos);
	void OnWheelDown(POINT mousePos);

	// 키 상태를 확인하는 함수
	bool IsButtonDown(eMouseButtonType buttonType);		// 처음 입력받았을시
	bool IsButtonPress(eMouseButtonType buttonType);	// 연속적 입력받을시
	bool IsButtonUp(eMouseButtonType buttonType);		// 입력을 뗄시
	bool IsButtonRelease(eMouseButtonType buttonType);	// 입력을 뗄시

private:
	friend class Input;
	
	POINT m_mousePos;
	POINT m_mouseRowPos;
	POINT m_clickDownPos;
	POINT m_clickUpPos;
	
	bool buttonStates[static_cast<int>(eMouseButtonType::Count)];			//현재 마우스 버튼 입력 상태
	bool buttonStatesBefore[static_cast<int>(eMouseButtonType::Count)];		//이전의 마우스 버튼 입력 상태

	bool m_iswheelUp;
	bool m_iswheelDown;
};