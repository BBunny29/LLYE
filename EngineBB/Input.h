#pragma once
#include <queue>
#include <tuple>
#include "Interface_EngineBB.h"

class KeyboardEvent;
// 이벤트 tuple로 만들거다
std::tuple<eKeyboardEvnet, unsigned char> keyboardEvent;

class MouseEvent;
// 얘는 enum으로만 받을거다


class Input : public IInput
{
public:
	Input();
	~Input();

	/// 키보드
	bool KeyIsPressed(const unsigned char keycode);			// 연속적 입력받을시
	bool KeyIsPressedFirst(const unsigned char keycode);	// 처음 입력받았을시
	bool KeyIsReleased(const unsigned char keycode);		// 입력을 뗄시

	bool KeyBufferIsEmpty();
	bool CharBufferIsEmpty();
	KeyboardEvent* ReadKey();
	unsigned char ReadChar();
	void OnKeyPressed(const unsigned char key);
	void OnKeyReleased(const unsigned char key);

	void SetCurrentBeforeKey();

	void OnChar(const unsigned char key);
	void EnableAutoRepeatKeys();
	void DisableAutoRepeatKeys();
	void EnableAutoRepeatChars();
	void DisableAutoRepeatChars();
	bool IsKeysAutoRepeat();
	bool IsCharsAutoRepeat();

private:
	bool autoRepeatKeys = false;
	bool autoRepeatChars = false;
	bool keyStates[256];			//현재 키입력 상태
	bool keyStatesBefore[256];		//방금 전의 키입력 상태
	std::queue<std::tuple<eKeyboardEvnet, unsigned char>> keyBuffer;
	std::queue<unsigned char> charBuffer;

	/// 마우스
public:
	void OnLeftPressed(int x, int y);
	void OnLeftReleased(int x, int y);
	void OnRightPressed(int x, int y);
	void OnRightReleased(int x, int y);
	void OnMiddlePressed(int x, int y);
	void OnMiddleReleased(int x, int y);
	void OnWheelUp(int x, int y);
	void OnWheelDown(int x, int y);
	void OnMouseMove(int x, int y);
	void OnMouseMoveRaw(int x, int y);


	bool IsLeftDown();
	bool IsMiddleDown();
	bool IsRightDown();

	int GetPosX();
	int GetPosY();
	POINT GetPos();

	bool EventBufferIsEmpty();
	MouseEvent ReadEvent();

private:
	std::queue<MouseEvent> eventBuffer;
	bool leftIsDown = false;
	bool rightIsDown = false;
	bool mbuttonDown = false;
	POINT m_mousePos;
	int x = 0;
	int y = 0;
};

