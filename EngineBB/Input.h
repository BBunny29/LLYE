#pragma once
#include <queue>
#include <tuple>
#include "Interface_EngineBB.h"

/// <summary>
/// Input(Ű����/���콺)�� �����ϴ� Ŭ����
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
	
	// ���� Ű���� ����(������ Update�ȿ��� ���峪�߿� �ҷ��� �Ѵ�)
	virtual void Update() override;

	// �Է¹ޱ�
	virtual void SetKeyboardState(eInput upDown, unsigned char keycode) override;
	virtual void SetMousePos(POINT mousePos) override;
	virtual void SetMouseRowPos(POINT mouseRowPos) override;
	virtual void SetMouseState(eInput upDown, eMouseButtonType mouseType, POINT clickPoint) override;
	virtual void SetMouseWheelState(eInput upDown, POINT clickPoint) override;

	// Ű���� �Է� Ȯ��
	virtual bool IsKeyDown(unsigned char keycode) override;
	virtual bool IsKeyPress(unsigned char keycode) override;
	virtual bool IsKeyUp(unsigned char keycode) override;
	virtual bool IsKeyRelease(unsigned char keycode) override;

	// ���콺 ��ġ(�ǽð�)
	virtual POINT GetMousePos() override;
	virtual POINT GetMouseRowPos() override;

	// ���콺 Ŭ�� ��ġ
	virtual POINT GetClickDownPos() override;
	virtual POINT GetClickUpPos() override;

	// ���콺 �Է� Ȯ��
	virtual bool IsDown(eMouseButtonType mouseType) override;
	virtual bool IsPress(eMouseButtonType mouseType) override;
	virtual bool IsUp(eMouseButtonType mouseType) override;
	virtual bool IsRelease(eMouseButtonType mouseType) override;
	
	// ���콺 ��
	virtual bool IsWheelUp() override;
	virtual bool IsWheelDown() override;

private:
	std::shared_ptr<class Keyboard> m_spKeyboard;
	std::shared_ptr<class Mouse> m_spMouse;
};

