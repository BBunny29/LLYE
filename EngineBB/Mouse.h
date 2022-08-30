#pragma once
#include <queue>
#include "Enum_EngineBB.h"

class Mouse
{
public:
	Mouse();
	~Mouse();

	// ���� ���콺��ư ���¸� �������·� �ű��
	void UpdateMouse();

	// ���콺 �̵� ������ �޴� �Լ�
	void OnMouseMove(POINT mousePos);
	void OnMouseMoveRaw(POINT mouseRowPos);
	
	// ���콺��ư ���¸� �����ϴ� �Լ�
	void OnButtonDown(eMouseButtonType buttonType, POINT clickPoint);
	void OnButtonUp(eMouseButtonType buttonType, POINT clickPoint);

	// ���콺�� ���¸� �����޴� �Լ�
	void OnWheelUp(POINT mousePos);
	void OnWheelDown(POINT mousePos);

	// Ű ���¸� Ȯ���ϴ� �Լ�
	bool IsButtonDown(eMouseButtonType buttonType);		// ó�� �Է¹޾�����
	bool IsButtonPress(eMouseButtonType buttonType);	// ������ �Է¹�����
	bool IsButtonUp(eMouseButtonType buttonType);		// �Է��� ����
	bool IsButtonRelease(eMouseButtonType buttonType);	// �Է��� ����

private:
	friend class Input;
	
	POINT m_mousePos;
	POINT m_mouseRowPos;
	POINT m_clickDownPos;
	POINT m_clickUpPos;
	
	bool buttonStates[static_cast<int>(eMouseButtonType::Count)];			//���� ���콺 ��ư �Է� ����
	bool buttonStatesBefore[static_cast<int>(eMouseButtonType::Count)];		//������ ���콺 ��ư �Է� ����

	bool m_iswheelUp;
	bool m_iswheelDown;
};