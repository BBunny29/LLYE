#pragma once
#include <queue>
#include <tuple>
#include "Interface_EngineBB.h"

class KeyboardEvent;
// �̺�Ʈ tuple�� ����Ŵ�
std::tuple<eKeyboardEvnet, unsigned char> keyboardEvent;

class MouseEvent;
// ��� enum���θ� �����Ŵ�


class Input : public IInput
{
public:
	Input();
	~Input();

	/// Ű����
	bool KeyIsPressed(const unsigned char keycode);			// ������ �Է¹�����
	bool KeyIsPressedFirst(const unsigned char keycode);	// ó�� �Է¹޾�����
	bool KeyIsReleased(const unsigned char keycode);		// �Է��� ����

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
	bool keyStates[256];			//���� Ű�Է� ����
	bool keyStatesBefore[256];		//��� ���� Ű�Է� ����
	std::queue<std::tuple<eKeyboardEvnet, unsigned char>> keyBuffer;
	std::queue<unsigned char> charBuffer;

	/// ���콺
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

