#pragma once
#include "DX11LibraryDefine.h"
#include "IRenderer.h"

class DX11Renderer : public IRenderer
{
public:
	DX11Renderer();
	~DX11Renderer();

	virtual bool Initialize(int hWnd, int screenWidth, int screenHeight) override;

	virtual void BeginRender() override;
	virtual void EndRender() override;
	virtual void Finalize() override;

public:
	virtual void Render() override;

private:
	// �̴ϼȶ������

private:
	HWND m_hWnd;
	unsigned int m_width = 0;
	unsigned int m_height = 0;

	/// �ʱ�ȭ ����
	D3D_DRIVER_TYPE m_D3DDriverType;
	D3D_FEATURE_LEVEL m_eFeatureLevel;
	
	Microsoft::WRL::ComPtr<ID3D11Device> m_spDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_spDeviceContext;
	
	class AdapterData* m_pAdapterManager;


	///����Ʈ ������ : ����� ���� �޸𸮸� �ڵ����� ����
	/*	GPU�� GPU�� �ڿ��� virtual representation�� ����.
		�ַ� ���ҽ�( ���۳� �ؽ��� �� )�� ������ ���� �������̽� */

	//���������ο� ���� �׷���ó���� ��Ÿ����
	//���ҽ��� �����ϰ� �����ϱ� ���� �������̽�
};
