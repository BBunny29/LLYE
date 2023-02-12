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
	virtual bool Initialize(int hWnd, int screenWidth, int screenHeight) abstract;
	virtual void Finalize() abstract;

	// ���� ���� �κ��� ���´�.
	virtual void BeginRender() abstract;
	// �������� �� �κ����� ����(Present) �۾��� �̷������.
	virtual void EndRender() abstract;
	virtual void Render() abstract;

	virtual void OnResize(int width, int height) abstract;

	/// Getter
	virtual HRESULT GetDeviceAndDeviceContext(void** device, void** deviceContext) abstract;

};