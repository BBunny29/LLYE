#pragma once

/// ���� ���ʰ� �Ǵ� Ŭ������ �������� �������̽���.
/// ��å���� �� ������ ����ϴ� ������ �پ��� �������� �ۼ��Ѵ�.
/// ���⼭ ���� Initialize�� ������, ���� �ش� �۾��� ���������� �ñ��.

/// 210629
/// �ʿ���� �������̽��� �����ؾ� �Ѵ�.
/// ������ �غ��� OpenGL ���� ������ �ʰ�����, ID3D12�� ����� ������ ���� �� ����.
class IRenderer abstract
{
public:
	IRenderer() {};
	virtual ~IRenderer() {};			// �Ҹ��ڸ� virtual�� ���� ���� ���, �ڽ� �Ҹ��ڰ� ȣ����� �ʴ´�.

public:
	// ���� �ʱ�ȭ �Լ�
	virtual bool Initialize(int hinst, int hWnd, int screenWidth, int screenHeight) abstract;

	// ������Ʈ
	virtual void Update(float deltaTIme) abstract;

	// ���� ���� �κ��� ���´�.
	virtual void BeginRender() abstract;

	// �������� �� �κ����� ����(Present) �۾��� �̷������.
	virtual void EndRender() abstract;

	// ������ �����Ѵ�.
	virtual void Finalize() abstract;

public:
	virtual void Render() abstract;
};
