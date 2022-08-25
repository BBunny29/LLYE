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

	/// Input(keyboard / mouse) ����
	virtual void SetInput(std::shared_ptr<__interface IInput>& _input) abstract;
	virtual std::shared_ptr<__interface IInput> GetInput() abstract;

	virtual LRESULT ImGuiHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) abstract;
};

__interface IInput
{
public:
	/// Ű����

	/// ���콺
};