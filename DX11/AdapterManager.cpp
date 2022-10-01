#include "pch.h"
#include "AdapterManager.h"

// ���漱�� ����� ��, static ������ ���������� ���� �ƶ�
/// static ��� ������ �̰��� ������ ������ �����Ͻ� ��ũ������ ����(����)
/// ���� ���� ������

AdapterManager::AdapterManager()
{
}

AdapterManager::~AdapterManager()
{
}

void AdapterManager::Initialize(Microsoft::WRL::ComPtr<ID3D11Device> pDevice)
{
	try
	{
		/// �� ID3D11Device�� ������ͼ� IDXGIDevice�� ���� �θ�(IDXGIAdapter)�� �θ�(IDXGIFactory)�� ã�Ƴ��� ������� IDXGIFactory�� �����;��ϴ��� �𸣰ڴ�.
		/// ���� ����� ����ϵ� CreateDXGIFactory�Լ��� ����� IDXGIFactory�� ����� ����� �Ȱ���.
		HRESULT hr;
		//Microsoft::WRL::ComPtr<IDXGIDevice> spDxgiDevice = nullptr;
		//hr = pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&spDxgiDevice);
		//
		//THROW_COM_ERROR_IF_FAILED(hr, "ID3D11Device QueryInterface ����");
		//
		//Microsoft::WRL::ComPtr<IDXGIAdapter> spDxgiAdapter = nullptr;
		//hr = spDxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&spDxgiAdapter);
		//
		//THROW_COM_ERROR_IF_FAILED(hr, "ID3D11Device GetParent ����");
		//
		//hr = spDxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_spDXGIFactory);
		//
		//THROW_COM_ERROR_IF_FAILED(hr, "DxgiAdpter GetParent ����");
				
		// Create a DXGIFactory object.
		hr = CreateDXGIFactory(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(m_cpDXGIFactory2.GetAddressOf()));
		THROW_COM_ERROR_IF_FAILED(hr, "DXGIFactory ���� ����");

		// �׷��� ī��/����� ������ ���� ComPtr
		Microsoft::WRL::ComPtr <IDXGIAdapter> spAdapter = nullptr;
		Microsoft::WRL::ComPtr <IDXGIOutput> spOutput = nullptr;

		UINT adapterIdx = 0;

		while (m_cpDXGIFactory2->EnumAdapters(adapterIdx, &spAdapter) != DXGI_ERROR_NOT_FOUND)
		{
			UINT outputIdx = 0;

			SetAdapterInfo(spAdapter);
			m_cpAdapters_V.push_back(spAdapter);

			while (spAdapter->EnumOutputs(outputIdx, &spOutput) != DXGI_ERROR_NOT_FOUND)
			{
				SetOutputInfo(spOutput);
				m_cpOutputs_V.push_back(spOutput);
				++outputIdx;
				spOutput = nullptr;
			}

			++adapterIdx;
			spAdapter = nullptr;
		}

		for (Microsoft::WRL::ComPtr<IDXGIOutput>& nowIDXGIOutput : m_cpOutputs_V)
		{
			// ���������� ���÷��� Mode�� �󼼸� �˱� ���� ����
			UINT numModes = 0;
			DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;
			UINT flags = DXGI_ENUM_MODES_INTERLACED;

			// GetDisplayModeList�� ������ ���ڿ� NULL�� �Ѱܼ� _numModes�� ���� �ľ��Ѵ�.
			hr = nowIDXGIOutput->GetDisplayModeList(format, flags, &numModes, NULL);

			THROW_COM_ERROR_IF_FAILED(hr, "IDXGIOutput GetDisplayModeList ����");

			// _numModes�� ũ�⿡ �°� DXGI_MODE_DESC�� ������(�迭)�� �����ϰ�, �̸� ���ڷ� �Ѱ� ä���´�.
			std::vector<DXGI_MODE_DESC> modeList_V(numModes);
			hr = nowIDXGIOutput->GetDisplayModeList(format, flags, &numModes, &modeList_V[0]);

			THROW_COM_ERROR_IF_FAILED(hr, "IDXGIOutput GetDisplayModeList ����");

			m_DXGIModes_V.push_back(modeList_V);
		}
	}
	catch (COMException& e)
	{
		ErrorLogger::Log(e);
	}
}

Microsoft::WRL::ComPtr<IDXGIFactory2> AdapterManager::GetDXGIFactory2()
{
	return m_cpDXGIFactory2;
}


DXGI_MODE_DESC* AdapterManager::GetDXGIModeDesc(int displayIdx, int Idx)
{
	//�ε��� �˻�
	if (displayIdx < 0 || displayIdx >= m_DXGIModes_V.size())
	{
		return nullptr;
	}
	else if (Idx < 0 || Idx >= m_DXGIModes_V[displayIdx].size())
	{
		return nullptr;
	}

	return &m_DXGIModes_V[displayIdx][Idx];
}


void AdapterManager::Finalize()
{
	m_cpDXGIFactory2->Release();
}

void AdapterManager::SetAdapterInfo(Microsoft::WRL::ComPtr<IDXGIAdapter> adapter)
{
	DXGI_ADAPTER_DESC dxgiAdapter;
	adapter->GetDesc(&dxgiAdapter);

	m_videoName_V.push_back(StringHelper::WStringToString(dxgiAdapter.Description));
	m_videoMemory_V.push_back((int)(dxgiAdapter.DedicatedVideoMemory / 1024));
}

void AdapterManager::SetOutputInfo(Microsoft::WRL::ComPtr<IDXGIOutput> output)
{
	DXGI_OUTPUT_DESC dxgiOutput;
	output->GetDesc(&dxgiOutput);

	m_displayResolution_V.push_back(dxgiOutput.DesktopCoordinates);
}
