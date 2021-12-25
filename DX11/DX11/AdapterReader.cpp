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
	// ����̽�/GPU ���� ȹ�� <��� #1> 
	// DXGI 1.1 / DXGI Factory ��� / DX11 �̻�� ����, DXGI 1.0 �� 1.1 ȥ�����. DXGI 1.3 �� Windows 8.1 �̻��ʼ�.

	// DXGI 1.1 ����
	// DXGI�������� �ٸ�

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


