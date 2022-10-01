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
		// Com오브젝트를 초기화(dds 외에 다른 텍스쳐를 사용하려면 써야함)
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

		// Forward의 렌더 타겟을 변경된 SwapChain의 ID3D11Texture2D 형식에 맞게 다시 만들어준다
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
	// 디버그에 사용할 렌더러를 먼저 그려준다
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
		// MSAA(MultiSampling Anti-Aliasing) 초기화만들기
		UINT MSAAQuality4x;
		HRESULT hr = m_cpDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &MSAAQuality4x);

		THROW_COM_ERROR_IF_FAILED(hr, "MSAA 초기화 실패");

		/// SwapChain 초기화 
		/// 현재 11.1 부터는 CreateSwapChain은 사용을 권장하고 있지 않다.
		/// CreateSwapChainForHwnd를 통해 스왑 체인을 만들 예정이다.
		/// 단, 이때 DXGI_SWAP_CHAIN_DESC 대신 DXGI_SWAP_CHAIN_DESC1을 사용한다.

		/// **** 스왑체인을 초기화할 때에는 반드시 모든 멤버 변수를 {0}으로 초기화하는 과정을 거쳐야한다.
		/// 하지 않을 경우, 스왑체인 포인터로 값을 반환해 올 수 없는 이슈가 발생해 초기화에 실패한다.
		/// 반드시 기억할 것!!

		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
		swapChainDesc.Width = m_width;
		swapChainDesc.Height = m_height;

		//_SwapChain.Format = m_pAdapterManager->GetDXGIModeDesc(0)->Format; // 아마 포멧이 너무 낮아서 일부러 높여서 쓰는듯. R8G8B8A8일것이다
		swapChainDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
		swapChainDesc.Stereo = false;

		/// 멀티샘플링 안티앨리어싱 적용 여부
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
		// DXGI_SWAP_EFFECT_DISCARD은 legacy한 bitblit형 모델이라 FLIP형 모델로 바꿨다.
		/// 바꾸려고 했다가 아직 못 바꿨다...
		/// dxgi1_4를 사용하는 것 같고, factory4를 이용한다
		/// 그렇게 수정도 해봤지만 아직 작동되지 않는다.

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC swapChainDescFull;
		swapChainDescFull.RefreshRate = m_spAdapterManager->GetDXGIModeDesc(0, 0)->RefreshRate;
		swapChainDescFull.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDescFull.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

		// 스왑체인 생성 시 Window모드가 아니라면 전체화면으로 창을 생성하게 된다.
		// 이때, WM_SIZE가 호출되어 콜백 함수로 점프한다.
		// 그러면 OnResize 등의 함수들이 자연스럽게 이어지게 된다.
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

