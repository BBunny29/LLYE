#include "pch.h"
#include "AdapterManager.h"

// 전방선언 비슷한 것, static 변수와 전역변수는 같은 맥락
/// static 멤버 변수는 이것을 해주지 않으면 컴파일시 링크에러가 난다(끔찍)
/// 절대 절대 해주자

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
		/// 왜 ID3D11Device를 가지고와서 IDXGIDevice를 만들어서 부모(IDXGIAdapter)의 부모(IDXGIFactory)를 찾아내는 방식으로 IDXGIFactory를 가져와야하는지 모르겠다.
		/// 위의 방법을 사용하든 CreateDXGIFactory함수를 사용해 IDXGIFactory를 만들든 결과는 똑같다.
		HRESULT hr;
		//Microsoft::WRL::ComPtr<IDXGIDevice> spDxgiDevice = nullptr;
		//hr = pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&spDxgiDevice);
		//
		//THROW_COM_ERROR_IF_FAILED(hr, "ID3D11Device QueryInterface 실패");
		//
		//Microsoft::WRL::ComPtr<IDXGIAdapter> spDxgiAdapter = nullptr;
		//hr = spDxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&spDxgiAdapter);
		//
		//THROW_COM_ERROR_IF_FAILED(hr, "ID3D11Device GetParent 실패");
		//
		//hr = spDxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_spDXGIFactory);
		//
		//THROW_COM_ERROR_IF_FAILED(hr, "DxgiAdpter GetParent 실패");
				
		// Create a DXGIFactory object.
		hr = CreateDXGIFactory(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(m_cpDXGIFactory2.GetAddressOf()));
		THROW_COM_ERROR_IF_FAILED(hr, "DXGIFactory 생성 실패");

		// 그래픽 카드/모니터 정보를 담을 ComPtr
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
			// 최종적으로 디스플레이 Mode의 상세를 알기 위한 과정
			UINT numModes = 0;
			DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;
			UINT flags = DXGI_ENUM_MODES_INTERLACED;

			// GetDisplayModeList의 마지막 인자에 NULL을 넘겨서 _numModes의 수를 파악한다.
			hr = nowIDXGIOutput->GetDisplayModeList(format, flags, &numModes, NULL);

			THROW_COM_ERROR_IF_FAILED(hr, "IDXGIOutput GetDisplayModeList 실패");

			// _numModes의 크기에 맞게 DXGI_MODE_DESC의 포인터(배열)를 생성하고, 이를 인자로 넘겨 채워온다.
			std::vector<DXGI_MODE_DESC> modeList_V(numModes);
			hr = nowIDXGIOutput->GetDisplayModeList(format, flags, &numModes, &modeList_V[0]);

			THROW_COM_ERROR_IF_FAILED(hr, "IDXGIOutput GetDisplayModeList 실패");

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
	//인덱스 검사
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
