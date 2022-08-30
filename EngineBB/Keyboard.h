#pragma once
#include <queue>

class KeyboardEvent;

class Keyboard
{
public:
	Keyboard();
	~Keyboard();

	// ���� Ű ���¸� �������·� �ű��
	void UpdateKeyboardState();

	// Ű ���¸� �����ϴ� �Լ�
	void OnKeyDown(const unsigned char keycode);
	void OnKeyUp(const unsigned char keycode);

	// Ű ���¸� Ȯ���ϴ� �Լ�
	bool IsKeyDown(const unsigned char keycode);	// ó�� �Է¹޾�����
	bool IsKeyPress(const unsigned char keycode);	// ������ �Է¹�����
	bool IsKeyUp(const unsigned char keycode);		// �Է��� ����
	bool IsKeyRelease(const unsigned char keycode);	// �Է��� ����

private:
	friend class Input;
	
	bool keyStates[256];			//���� Ű�Է� ����
	bool keyStatesBefore[256];		//������ Ű�Է� ����
};