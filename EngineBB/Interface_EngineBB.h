#pragma once
#include "Enum_EngineBB.h"
/// �ܺ� ������Ʈ�� ����� EngineBB�� �������̽��鸸 ��Ƴ��� .h

/// <summary>
/// ������ �������̽�(������)
/// �ٱ��κ�(���� ������Ʈ)���� ����� �Լ��鸸 �����Լ��� �����.
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

	/// Input(keyboard / mouse) ����
	virtual void SetInput(std::shared_ptr<__interface IInput>& _input) abstract;
	virtual std::shared_ptr<__interface IInput> GetInput() abstract;

	/// Imgui �ڵ� ����
	virtual LRESULT ImGuiHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) abstract;
};

__interface IInput
{
public:
	virtual bool Initialize() abstract;
	virtual void Finalize() abstract;

	// ���� Ű���� ����(Update�Ǳ� �� ������� �ҷ��� �Ѵ�)
	virtual void Update() abstract;
	
	// �Է¹ޱ�
	virtual void SetKeyboardState(eInput upDown, unsigned char keycode) abstract;
	virtual void SetMousePos(POINT mousePos) abstract;
	virtual void SetMouseRowPos(POINT mouseRowPos) abstract;
	virtual void SetMouseState(eInput upDown, eMouseButtonType mouseType, POINT clickPoint) abstract;
	virtual void SetMouseWheelState(eInput upDown, POINT clickPoint) abstract;

	// Ű���� �Է� Ȯ��
	virtual bool IsKeyDown(unsigned char keycode) abstract;		// Ű�� ������ �� �ѹ� true
	virtual bool IsKeyPress(unsigned char keycode) abstract;	// Ű�� ������������ �׻� true
	virtual bool IsKeyUp(unsigned char keycode) abstract;		// Ű�� �ö󰥶� �ѹ� True
	virtual bool IsKeyRelease(unsigned char keycode) abstract;	// Ű�� ���������� �׻� True

	// ���콺 ��ġ(�ǽð�)
	virtual POINT GetMousePos() abstract;
	virtual POINT GetMouseRowPos() abstract;

	// ���콺 Ŭ�� ��ġ
	virtual POINT GetClickDownPos() abstract;
	virtual POINT GetClickUpPos() abstract;

	// ���콺 �Է� Ȯ��
	virtual bool IsDown(eMouseButtonType mouseType) abstract;
	virtual bool IsPress(eMouseButtonType mouseType) abstract;
	virtual bool IsUp(eMouseButtonType mouseType) abstract;
	virtual bool IsRelease(eMouseButtonType mouseType) abstract;

	// ���콺 ��
	virtual bool IsWheelUp() abstract;
	virtual bool IsWheelDown() abstract;
};