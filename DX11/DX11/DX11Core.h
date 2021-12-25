#pragma once
#include <vector>
#include "DX11Define.h"

class DX11Core
{
public:
	DX11Core();
	~DX11Core();

public:
	bool Initialize(HWND hWnd);
	
	void ClearMainRenderTarget();
	void SetMainRenderTarget();
	void SetMainViewport();
	void SetHalfViewport();
	void SetHalfHalfViewport();
	void SetDefaultStates();
	void ClearShaderResources();
	void Present();
	void Debug();

private:

private:
	Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_NormalDSS;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_MainRenderTargetView;

	D3D_FEATURE_LEVEL m_FeatureLevel;		// Status or DirectX Info

	IDXGIOutput* m_Output;
	DXGI_ADAPTER_DESC1 m_AdapterDesc1;		// ¾î´ðÅÍ Á¤º¸

private:
	D3D11_VIEWPORT m_ScreenViewport;
	D3D11_VIEWPORT m_ScreenHalfViewport;
	D3D11_VIEWPORT m_ScreenHalfHalfViewport;



	ID3D11DepthStencilView* m_DepthStencilView;
	ID3D11Texture2D* m_DepthStencilBuffer;
};

