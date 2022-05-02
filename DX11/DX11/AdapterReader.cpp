#include "pch.h"
#include "AdapterReader.h"

using namespace Microsoft::WRL;

AdapterData::AdapterData(Microsoft::WRL::ComPtr<IDXGIAdapter> pAdapter)
{
	this->m_spAdapter = pAdapter;
	HRESULT hr = pAdapter->GetDesc(&this->m_description);
	//if (FAILED(hr))
	//{
	//	ErrorLogger::Log(hr, "Failed to Get Description for IDXGIAdapter.");
	//}
}

std::vector<AdapterData> AdapterReader::GetAdapters()
{
	// 디바이스/GPU 정보 획득 <방법 #1> 
	// DXGI 1.1 / DXGI Factory 사용 / DX11 이상시 권장, DXGI 1.0 과 1.1 혼용금지. DXGI 1.3 은 Windows 8.1 이상필수.

	// DXGI 1.1 대응
	// DXGI버전별로 다름

	//If already initialized
	if (m_adapter_V.size() > 0)
	{
		return m_adapter_V;
	}

	Microsoft::WRL::ComPtr<IDXGIFactory1> pFactory;

	// Create a DXGIFactory object.
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf()));

	IDXGIAdapter* pAdapter;
	UINT index = 0;
	while (SUCCEEDED(pFactory->EnumAdapters(index, &pAdapter)))
	{
		m_adapter_V.push_back(AdapterData(pAdapter));
		index += 1;
	}
	return m_adapter_V;
}


