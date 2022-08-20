#include "pch.h"
#include "DX11Renderer.h"
#include "AdapterReader.h"

DX11Renderer::DX11Renderer()
	: m_hWnd(nullptr)
	, m_width(0)
	, m_height(0)
	
	, m_D3DDriverType(D3D_DRIVER_TYPE_HARDWARE)
	, m_eFeatureLevel()

	, m_spDevice(nullptr)
	, m_spDeviceContext(nullptr)

	, m_pAdapterManager(nullptr)
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
			nullptr,						// default adapter
			m_D3DDriverType,
			nullptr,						// no software device
			createDeviceFlags,
			featureLevels,
			ARRAYSIZE(featureLevels),       // default feature level array
			D3D11_SDK_VERSION,
			m_spDevice.GetAddressOf(),
			&m_eFeatureLevel,
			m_spDeviceContext.GetAddressOf());
		THROW_COM_ERROR_IF_FAILED(hr, "Fail CreateDevice Fail");

		if (m_eFeatureLevel != D3D_FEATURE_LEVEL_11_0)
		{
			MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
			return false;
		}

		m_pAdapterManager = new AdapterData();

		m_pAdapterManager->Initialize(m_spDevice);
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
}

void DX11Renderer::EndRender()
{
}

void DX11Renderer::Finalize()
{
}

void DX11Renderer::Render()
{
}

