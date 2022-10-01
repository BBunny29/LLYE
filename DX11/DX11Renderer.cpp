#include "pch.h"
#include "DX11Renderer.h"

#include "AdapterManager.h"
#include "RenderTargetView.h"
#include "RasterizerState.h"

#include "Forward.h"
#include "Box.h"

DX11Renderer::DX11Renderer()
	: m_hWnd(nullptr)

	, m_width(0)
	, m_height(0)

	, m_enable4xMsaa(false)
	
	, m_D3DDriverType(D3D_DRIVER_TYPE_HARDWARE)
	, m_eFeatureLevel()

	, m_cpDevice(nullptr)
	, m_cpDeviceContext(nullptr)

	, m_spAdapterManager(nullptr)
	, m_cpSwapchain(nullptr)
	, m_Forward(nullptr)
{
}

DX11Renderer::~DX11Renderer()
{
}

bool DX11Renderer::Initialize(int hwnd, int screenWidth, int screenHeight)
{
	m_hWnd = reinterpret_cast<HWND>(hwnd);

	m_width = screenWidth;
	m_height = screenHeight;

	UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;

#endif // DEBUG || _DEBUG

	try
	{
		// Com������Ʈ�� �ʱ�ȭ(dds �ܿ� �ٸ� �ؽ��ĸ� ����Ϸ��� �����)
		HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
		THROW_COM_ERROR_IF_FAILED(hr, "Fail COInitialize Fail");

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1
		};

		hr = D3D11CreateDevice(
			nullptr,					// default adapter
			m_D3DDriverType,
			nullptr,					// no software device
			createDeviceFlags,
			featureLevels,
			ARRAYSIZE(featureLevels),       // default feature level array
			D3D11_SDK_VERSION,
			m_cpDevice.GetAddressOf(),
			&m_eFeatureLevel,
			m_cpDeviceContext.GetAddressOf());

		THROW_COM_ERROR_IF_FAILED(hr, "Fail CreateDevice Fail");

		if (m_eFeatureLevel != D3D_FEATURE_LEVEL_11_0)
		{
			MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
			return false;
		}

		m_spAdapterManager = std::make_shared<AdapterManager>();
		m_spAdapterManager->Initialize(m_cpDevice);
		
		CreateSwapChain();

		Microsoft::WRL::ComPtr<ID3D11Texture2D> _backBuffer = nullptr;
		hr = m_cpSwapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(_backBuffer.GetAddressOf()));

		THROW_COM_ERROR_IF_FAILED(hr, "SwapChain1 GetBuffer Fail");

		// Forward�� ���� Ÿ���� ����� SwapChain�� ID3D11Texture2D ���Ŀ� �°� �ٽ� ������ش�
		m_Forward = std::make_shared<Forward>();
		m_Forward->Initialize(m_cpDevice.Get(), m_width, m_height);
		m_Forward->OnResize(m_cpDevice.Get(), m_width, m_height);
		m_Forward->GetRenderTarget()->CreateRTVFromID3D11Texture(m_cpDevice.Get(), _backBuffer.Get());
		m_Forward->SetViewports(m_cpDeviceContext);

		m_TestBox = std::make_shared<Box>();
		m_TestBox->Initialize(m_cpDevice.Get(), m_cpDeviceContext.Get(), , );
	}
	catch (COMException& exception)
	{
		ErrorLogger::Log(exception);
		return false;
	}

	return true;
}

void DX11Renderer::BeginRender()
{
	// ����׿� ����� �������� ���� �׷��ش�
	m_cpDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_cpDeviceContext->RSSetState(RasterizerState::GetSolidNormal());
	m_cpDeviceContext->OMSetDepthStencilState(RasterizerState::GetDepthStencilState(), 0);
	m_cpDeviceContext->OMSetBlendState(RasterizerState::GetBlenderState(), NULL, 0xFFFFFFFF);
	m_cpDeviceContext->PSSetSamplers(0, 1, RasterizerState::GetLinearSamplerStateAddressOf());
	m_cpDeviceContext->RSSetViewports(1, &m_pRenderTarget->GetViewPort());

	m_Forward->BeginRender(m_cpDeviceContext);
}

void DX11Renderer::EndRender()
{
}

void DX11Renderer::CreateSwapChain()
{
	try
	{
		// MSAA(MultiSampling Anti-Aliasing) �ʱ�ȭ�����
		UINT MSAAQuality4x;
		HRESULT hr = m_cpDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &MSAAQuality4x);

		THROW_COM_ERROR_IF_FAILED(hr, "MSAA �ʱ�ȭ ����");

		/// SwapChain �ʱ�ȭ 
		/// ���� 11.1 ���ʹ� CreateSwapChain�� ����� �����ϰ� ���� �ʴ�.
		/// CreateSwapChainForHwnd�� ���� ���� ü���� ���� �����̴�.
		/// ��, �̶� DXGI_SWAP_CHAIN_DESC ��� DXGI_SWAP_CHAIN_DESC1�� ����Ѵ�.

		/// **** ����ü���� �ʱ�ȭ�� ������ �ݵ�� ��� ��� ������ {0}���� �ʱ�ȭ�ϴ� ������ ���ľ��Ѵ�.
		/// ���� ���� ���, ����ü�� �����ͷ� ���� ��ȯ�� �� �� ���� �̽��� �߻��� �ʱ�ȭ�� �����Ѵ�.
		/// �ݵ�� ����� ��!!

		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
		swapChainDesc.Width = m_width;
		swapChainDesc.Height = m_height;

		//_SwapChain.Format = m_pAdapterManager->GetDXGIModeDesc(0)->Format; // �Ƹ� ������ �ʹ� ���Ƽ� �Ϻη� ������ ���µ�. R8G8B8A8�ϰ��̴�
		swapChainDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
		swapChainDesc.Stereo = false;

		/// ��Ƽ���ø� ��Ƽ�ٸ���� ���� ����
		if (m_enable4xMsaa)
		{
			swapChainDesc.SampleDesc.Count = 4;
			swapChainDesc.SampleDesc.Quality = MSAAQuality4x - 1;
		}
		else
		{
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;
		}

		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2;
		swapChainDesc.Flags = 0;
		swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		//swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		// DXGI_SWAP_EFFECT_DISCARD�� legacy�� bitblit�� ���̶� FLIP�� �𵨷� �ٲ��.
		/// �ٲٷ��� �ߴٰ� ���� �� �ٲ��...
		/// dxgi1_4�� ����ϴ� �� ����, factory4�� �̿��Ѵ�
		/// �׷��� ������ �غ����� ���� �۵����� �ʴ´�.

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC swapChainDescFull;
		swapChainDescFull.RefreshRate = m_spAdapterManager->GetDXGIModeDesc(0, 0)->RefreshRate;
		swapChainDescFull.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDescFull.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

		// ����ü�� ���� �� Window��尡 �ƴ϶�� ��üȭ������ â�� �����ϰ� �ȴ�.
		// �̶�, WM_SIZE�� ȣ��Ǿ� �ݹ� �Լ��� �����Ѵ�.
		// �׷��� OnResize ���� �Լ����� �ڿ������� �̾����� �ȴ�.
		swapChainDescFull.Windowed = true;

		hr = m_spAdapterManager->GetDXGIFactory2()->CreateSwapChainForHwnd(
			m_cpDevice.Get(),
			m_hWnd,
			&swapChainDesc,
			&swapChainDescFull,
			nullptr,
			&m_cpSwapchain);

		THROW_COM_ERROR_IF_FAILED(hr, "CreateSwapChainForHwnd Fail");

	}
	catch (COMException& exception)
	{
		ErrorLogger::Log(exception);
	}
}

void DX11Renderer::Finalize()
{
	m_spAdapterManager->Finalize();
}

void DX11Renderer::Render()
{
}

void DX11Renderer::OnResize(int width, int height)
{
	m_width = width;
	m_height = height;

	CreateSwapChain();
	m_Forward->OnResize(m_cpDevice.Get(), m_width, m_height);

}

