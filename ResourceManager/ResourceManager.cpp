#include "pch.h"
#include "IRenderer.h"

#include "ResourceManager.h"

ResourceManager::ResourceManager()
	: m_D3DDriverType(D3D_DRIVER_TYPE_HARDWARE)	
	, m_eFeatureLevel()
{
}

ResourceManager::~ResourceManager()
{
}

bool ResourceManager::Initialize(std::shared_ptr<IRenderer> pRenderer)
{
//	UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
//
//#ifdef _DEBUG
//	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
//
//#endif // DEBUG || _DEBUG
//
//	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
//	//COM_ERROR_IF_FAILED(hr, "COInitialize Fail");
//
//	D3D_FEATURE_LEVEL featureLevels[] =
//	{
//		D3D_FEATURE_LEVEL_11_0,
//		D3D_FEATURE_LEVEL_10_1,
//		D3D_FEATURE_LEVEL_10_0,
//		D3D_FEATURE_LEVEL_9_3,
//		D3D_FEATURE_LEVEL_9_2,
//		D3D_FEATURE_LEVEL_9_1
//	};
//
//	hr = D3D11CreateDevice(
//		nullptr,                 // default adapter
//		m_D3DDriverType,
//		nullptr,                 // no software device
//		createDeviceFlags,
//		featureLevels,
//		ARRAYSIZE(featureLevels),              // default feature level array
//		D3D11_SDK_VERSION,
//		&m_pDevice,
//		&m_eFeatureLevel,
//		&m_pDeviceContext);

	/// 렌더러 nullptr 체크해야함
	pRenderer->GetDeviceAndDeviceContext((void**)&m_pDevice, (void**)&m_pDeviceContext);
	m_pRenderer = pRenderer;

	return true;
}

int ResourceManager::GetInfo()
{
	return 0;
}
