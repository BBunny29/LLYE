#include "pch.h"
#include "AdapterReader.h"

// 전방선언 비슷한 것, static 변수와 전역변수는 같은 맥락
/// static 멤버 변수는 이것을 해주지 않으면 컴파일시 링크에러가 난다(끔찍)
/// 절대 절대 해주자

//std::vector<AdapterData> AdapterReader::m_adapter_V;

AdapterData::AdapterData()
{
}

AdapterData::~AdapterData()
{
}

void AdapterData::Initialize(Microsoft::WRL::ComPtr<ID3D11Device> pDevice)
{
	HRESULT hr;
	Microsoft::WRL::ComPtr<IDXGIDevice> _dxgiDevice = nullptr;
	hr = pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&_dxgiDevice);

	Microsoft::WRL::ComPtr<IDXGIAdapter> _dxgiAdapter = nullptr;
	hr = _dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&_dxgiAdapter);

	hr = _dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), (void**)&m_DXGIFactory);


}

AdapterData::AdapterData(Microsoft::WRL::ComPtr<IDXGIAdapter> pAdapter)
{
	this->m_spAdapter = pAdapter;
	HRESULT hr = pAdapter->GetDesc(&this->m_description);
	if (FAILED(hr))
	{
		//ErrorLogger::Log(hr, "Failed to Get Description for IDXGIAdapter.");
	}
}

//std::vector<AdapterData> AdapterData::GetAdapters()
//{
//	// 디바이스/GPU 정보 획득 <방법 #1> 
//	// DXGI 1.1 / DXGI Factory 사용 / DX11 이상시 권장, DXGI 1.0 과 1.1 혼용금지. DXGI 1.3 은 Windows 8.1 이상필수.
//
//	// DXGI 1.1 대응
//	// DXGI버전별로 다름
//
//	if (m_adapter_V.size() > 0)
//	{
//		return m_adapter_V;
//	}
//
//	Microsoft::WRL::ComPtr<IDXGIFactory1> pFactory;
//
//	// Create a DXGIFactory object.
//	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf()));
//
//	IDXGIAdapter* pAdapter;
//	UINT index = 0;
//	while (SUCCEEDED(pFactory->EnumAdapters(index, &pAdapter)))
//	{
//		//m_adapter_V.push_back(AdapterData(pAdapter));
//		index += 1;
//	}
//	
//	return m_adapter_V;
//}
