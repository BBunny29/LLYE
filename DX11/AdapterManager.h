#pragma once
#include <vector>
#include "DX11Define.h"

/// <summary>
/// 어댑터(GPU) 정보를 가지고 있는 클래스
/// IDXGISwapChain을 생성하기위해 필요하다
/// IDXGIFactory를 생성하고 그래픽카드(IDXGIAdapter)와 모니터 정보(IDXGIOutput)를 읽어와 가지고 있는다.
/// 
/// 2022. 09. 19 B.Bunny
/// </summary>
class AdapterManager
{
public:
	AdapterManager();
	~AdapterManager();

	void Initialize(Microsoft::WRL::ComPtr<ID3D11Device> pDevice);
	void Finalize();
	
	Microsoft::WRL::ComPtr<IDXGIFactory2> GetDXGIFactory2();
	DXGI_MODE_DESC* GetDXGIModeDesc(int displayIdx, int Idx);

private:
	void SetAdapterInfo(Microsoft::WRL::ComPtr<IDXGIAdapter> adapter);
	void SetOutputInfo(Microsoft::WRL::ComPtr<IDXGIOutput> output);

private:
	Microsoft::WRL::ComPtr<IDXGIFactory2> m_cpDXGIFactory2 = nullptr; // 스왑체인을 만들때도 사용되는 IDXGIFactory
			
	std::vector<Microsoft::WRL::ComPtr<IDXGIAdapter>> m_cpAdapters_V;	/// 그래픽카드들
	std::vector<Microsoft::WRL::ComPtr<IDXGIOutput>> m_cpOutputs_V;		/// 모니터(화면)

	std::vector<std::string> m_videoName_V;		// GPU의 이름(IDXGIAdapter DESC의 멤버)
	std::vector<int> m_videoMemory_V;			// GPU 메모리 크기(IDXGIAdapter DESC의 멤버) : CPU와 공유되지 않는 전용 비디오 메모리의 바이트수
	std::vector<RECT> m_displayResolution_V;					// 화면들의 해상도 (IDXGIOutput DESC의 멤버)
	std::vector<std::vector<DXGI_MODE_DESC>> m_DXGIModes_V;		// 화면의 디스플레이 모드들(IDXGIOutput DESC의 멤버)

	/// 이 두 정보를 엔진으로 보내서 화면크기나 해상도를 선택할수있게 할거다(창화면, 전체화면)
	std::tuple<Microsoft::WRL::ComPtr<IDXGIAdapter>, std::vector<std::string>, std::vector<int> > a;
	std::tuple<Microsoft::WRL::ComPtr<IDXGIOutput>, std::vector<RECT>, std::vector<DXGI_MODE_DESC>> b;
};


/*
typedef struct DXGI_ADAPTER_DESC
{
	WCHAR  Description[128];        // 어댑터 설명,
	UINT   VendorId;                // 하드웨어 공급업체의 PCI ID
	UINT   DeviceId;                // 하드웨어 장치의 PCI ID
	UINT   SubSysId;                // 서브시스템의 PCI ID
	UINT   Revision;                // 어댑터 개정(revision) 번호의 PCI ID
	SIZE_T DedicatedVideoMemory;    // CPU와 공유되지 않은 전용 비디오 메모리의 바이트 수
	SIZE_T DedicatedSystemMemory;   // CPU와 공유되지 않는 전용 시스템 메로리 바이트 수
	SIZE_T SharedSystemMemory;      // 공유 시스템 메모리의 바이트 수
	LUID   AdapterLuid;             // 어댑터를 식별하는 고유값(Locally Unique Identifier)
} DXGI_ADAPTER_DESC;
*/

/*
typedef struct DXGI_MODE_DESC {
  UINT                     Width;				// 해상도 가로
  UINT                     Height;				// 해상도 세로
  DXGI_RATIONAL            RefreshRate;			// 주사율 (Numerator 분자 / Denominator 분모) 
  DXGI_FORMAT              Format;				// 디스플레이 형식(DXGI_FORMAT_R32_UNIT 등)
  DXGI_MODE_SCANLINE_ORDER ScanlineOrdering;	// 스캔 방식 : 순차 주소(프로그레시브) 또는 비월 주소(인터레이스) 
  DXGI_MODE_SCALING        Scaling;				// 해상도에 맞게 이미지의 스케일링 처리를 어떻게 할지 // 영상을 모니터 크기에 맞게 늘리거나 줄이는 방식
} DXGI_MODE_DESC;
*/