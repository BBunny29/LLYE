#include "pch.h"
#include "Forward.h"

#include "RenderTargetView.h"
#include "DepthStencilView.h"
#include "RasterizerState.h"

Forward::Forward()
{

}

Forward::~Forward()
{

}


void Forward::Initialize(ID3D11Device* pDevice, UINT width, UINT height)
{

	if (m_spDepthStencil == nullptr || m_spRenderTarget == nullptr)
	{
		m_spRenderTarget = std::make_shared<RenderTargetView>();
		m_spDepthStencil = std::make_shared<DepthStencilView>();
	}
	else
	{
		m_spRenderTarget.reset();
		m_spDepthStencil.reset();
	}

	try
	{
		HRESULT _hr;

		_hr = m_spRenderTarget->Initialize(pDevice, width, height,
			D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE,
			DXGI_FORMAT_R16G16B16A16_FLOAT,
			DXGI_FORMAT_R16G16B16A16_FLOAT,
			DXGI_FORMAT_R16G16B16A16_FLOAT);

		THROW_COM_ERROR_IF_FAILED(_hr, "Rendertarget Initialize Failed");

		_hr = m_spDepthStencil->Initialize(pDevice, width, height,
			D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE,	// 그냥 BIND_DEPTH_STENCIL만 하면 오류가..
			DXGI_FORMAT_R24G8_TYPELESS,
			DXGI_FORMAT_R24_UNORM_X8_TYPELESS,
			DXGI_FORMAT_D24_UNORM_S8_UINT);

		THROW_COM_ERROR_IF_FAILED(_hr, "DepthStencil Initialize Failed");

	}
	catch (COMException& e)
	{
		ErrorLogger::Log(e);
	}
}

void Forward::OnResize(ID3D11Device* pDevice, UINT width, UINT height)
{

	if (m_spDepthStencil == nullptr || m_spRenderTarget == nullptr)
	{
		m_spRenderTarget = std::make_shared<RenderTargetView>();
		m_spDepthStencil = std::make_shared<DepthStencilView>();
	}
	else
	{
		m_spRenderTarget.reset();
		m_spDepthStencil.reset();
	}

	try
	{
		HRESULT _hr;

		m_spRenderTarget = std::make_shared<RenderTargetView>();
		_hr = m_spRenderTarget->Initialize(pDevice, width, height,
			D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE,
			DXGI_FORMAT_R16G16B16A16_FLOAT,
			DXGI_FORMAT_R16G16B16A16_FLOAT,
			DXGI_FORMAT_R16G16B16A16_FLOAT);

		THROW_COM_ERROR_IF_FAILED(_hr, "Rendertarget Initialize Failed");

		m_spDepthStencil = std::make_shared<DepthStencilView>();
		_hr = m_spDepthStencil->Initialize(pDevice, width, height,
			D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE,	// 그냥 BIND_DEPTH_STENCIL만 하면 오류가..
			DXGI_FORMAT_R24G8_TYPELESS,
			DXGI_FORMAT_R24_UNORM_X8_TYPELESS,
			DXGI_FORMAT_D24_UNORM_S8_UINT);

		THROW_COM_ERROR_IF_FAILED(_hr, "DepthStencil Initialize Failed");

	}
	catch (COMException& e)
	{
		ErrorLogger::Log(e);
	}
}

void Forward::SetViewports(Microsoft::WRL::ComPtr<ID3D11DeviceContext> pDeviceContext)
{
	pDeviceContext->RSSetViewports(1, &m_spRenderTarget->GetViewPort());
}

RenderTargetView* Forward::GetRenderTarget()
{
	return m_spRenderTarget.get();
}

DepthStencilView* Forward::GetDepthStencil()
{
	return m_spDepthStencil.get();
}

std::shared_ptr<RenderTargetView> Forward::GetRenderTargetView()
{
	return m_spRenderTarget;
}

void Forward::BeginRender(Microsoft::WRL::ComPtr<ID3D11DeviceContext> pDeviceContext)
{
	ID3D11RenderTargetView* renderTargets[1] = { m_spRenderTarget->GetRenderTargerViewRawptr() };
	pDeviceContext->OMSetRenderTargets(1, renderTargets, m_spDepthStencil->GetDepthSetncilView());

	float bgcolor[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	pDeviceContext->ClearRenderTargetView(m_spRenderTarget->GetRenderTargerViewRawptr(), bgcolor);
	pDeviceContext->ClearDepthStencilView(m_spDepthStencil->GetDepthSetncilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// 뷰포트를 설정합니다.
	pDeviceContext->RSSetViewports(1, &m_spRenderTarget->GetViewPort());
}
