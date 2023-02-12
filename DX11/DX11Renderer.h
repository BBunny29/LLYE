#pragma once
#include "DX11LibraryDefine.h"
#include "IRenderer.h"

/// <summary>
/// ������
/// 
/// 2023.01.03 B.Bunny
/// </summary>
class DX11Renderer : public IRenderer
{
public:
	DX11Renderer();
	~DX11Renderer();

	virtual bool Initialize(int hWnd, int screenWidth, int screenHeight) override;
	virtual void Finalize() override;

	virtual void BeginRender() override;
	virtual void EndRender() override;
	virtual void Render() override;

	virtual void OnResize(int width, int height) override;

private:
	void CreateSwapChain();

public:
	/// Getter
	virtual HRESULT GetDeviceAndDeviceContext(void** device, void** deviceContext) override;

private:
	HWND m_hWnd;
	unsigned int m_width = 0;
	unsigned int m_height = 0;

	bool m_enable4xMsaa;

	/// �ʱ�ȭ ����
	D3D_DRIVER_TYPE m_D3DDriverType;
	D3D_FEATURE_LEVEL m_eFeatureLevel;
	
	/// ����̽��� ����̽� ���ؽ�Ʈ
	Microsoft::WRL::ComPtr<ID3D11Device> m_cpDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_cpDeviceContext;
	
	std::shared_ptr<class AdapterManager> m_spAdapterManager;
	
	//Front Buffer( ���� ȭ�鿡 �������� ���� )�� Back Buffer( ���� ������ �ؼ� ����ϴ� ���� ) �� �غ��ؼ� �̰��� Flip ��Ű�鼭 ������ ���鼭 �����ִ� ��
	Microsoft::WRL::ComPtr<IDXGISwapChain1> m_cpSwapchain;

	std::shared_ptr<class Forward> m_Forward;

	///����Ʈ ������ : ����� ���� �޸𸮸� �ڵ����� ����
	/*	GPU�� GPU�� �ڿ��� virtual representation�� ����.
		�ַ� ���ҽ�( ���۳� �ؽ��� �� )�� ������ ���� �������̽� */

	//���������ο� ���� �׷���ó���� ��Ÿ����
	//���ҽ��� �����ϰ� �����ϱ� ���� �������̽�
	std::shared_ptr<class Box> m_TestBox;

};
