#pragma once
#include "DX11Define.h"

/// <summary>
/// 포워드 렌더링을 관리한다
/// 
/// 2022. 09. 29 B.Bunny
/// </summary>
class Forward
{
public:
	Forward();
	~Forward();

	void Initialize(ID3D11Device* pDevice, UINT width, UINT height);
	void OnResize(ID3D11Device* pDevice, UINT width, UINT height);
	void SetViewports(Microsoft::WRL::ComPtr<ID3D11DeviceContext> pDeviceContext);

	class RenderTargetView* GetRenderTarget();
	class DepthStencilView* GetDepthStencil();

	std::shared_ptr<class RenderTargetView> GetRenderTargetView();

	// OMSetRenderTargets
	// ClearRenderTargetView
	// ClearDepthStencilView
	// IASetPrimitiveTopology
	// RSSetState
	// OMSetDepthStencilState 
	// OMSetBlendState
	// PSSetSamplers
	void BeginRender(Microsoft::WRL::ComPtr<ID3D11DeviceContext> pDeviceContext);


public:
	std::shared_ptr<class RenderTargetView> m_spRenderTarget;

private:
	std::shared_ptr<class DepthStencilView> m_spDepthStencil;

};