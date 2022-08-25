#pragma once

/// <summary>
/// �������� �������̽�(������)
/// �ٱ��κ�(����)���� ����� �Լ��鸸 �����Լ��� �����.
/// 
/// 2022.08.21 B.Bunny
/// </summary>
__interface IRenderer
{
public:
	// ������ �ʱ�ȭ �Լ�
	virtual bool Initialize(int hWnd, int screenWidth, int screenHeight) abstract;

	// ���� ���� �κ��� ���´�.
	virtual void BeginRender() abstract;

	virtual void Render() abstract;

	// �������� �� �κ����� ����(Present) �۾��� �̷������.
	virtual void EndRender() abstract;

	// ������ �����Ѵ�.
	virtual void Finalize() abstract;

};