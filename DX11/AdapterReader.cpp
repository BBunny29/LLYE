#include "pch.h"
#include "AdapterReader.h"

// ���漱�� ����� ��, static ������ ���������� ���� �ƶ�
/// static ��� ������ �̰��� ������ ������ �����Ͻ� ��ũ������ ����(����)
/// ���� ���� ������

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
//	// ����̽�/GPU ���� ȹ�� <��� #1> 
//	// DXGI 1.1 / DXGI Factory ��� / DX11 �̻�� ����, DXGI 1.0 �� 1.1 ȥ�����. DXGI 1.3 �� Windows 8.1 �̻��ʼ�.
//
//	// DXGI 1.1 ����
//	// DXGI�������� �ٸ�
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
