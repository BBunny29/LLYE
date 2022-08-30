#pragma once
#include <queue>

class KeyboardEvent;

class Keyboard
{
public:
	Keyboard();
	~Keyboard();

	// 현재 키 상태를 이전상태로 옮긴다
	void UpdateKeyboardState();

	// 키 상태를 설정하는 함수
	void OnKeyDown(const unsigned char keycode);
	void OnKeyUp(const unsigned char keycode);

	// 키 상태를 확인하는 함수
	bool IsKeyDown(const unsigned char keycode);	// 처음 입력받았을시
	bool IsKeyPress(const unsigned char keycode);	// 연속적 입력받을시
	bool IsKeyUp(const unsigned char keycode);		// 입력을 뗄시
	bool IsKeyRelease(const unsigned char keycode);	// 입력을 뗄시

private:
	friend class Input;
	
	bool keyStates[256];			//현재 키입력 상태
	bool keyStatesBefore[256];		//이전의 키입력 상태
};