#pragma once
#include <vector>
#include "DX11Define.h"

/// <summary>
/// �����(GPU) ������ ������ �ִ� Ŭ����
/// IDXGISwapChain�� �����ϱ����� �ʿ��ϴ�
/// IDXGIFactory�� �����ϰ� �׷���ī��(IDXGIAdapter)�� ����� ����(IDXGIOutput)�� �о�� ������ �ִ´�.
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
	Microsoft::WRL::ComPtr<IDXGIFactory2> m_cpDXGIFactory2 = nullptr; // ����ü���� ���鶧�� ���Ǵ� IDXGIFactory
			
	std::vector<Microsoft::WRL::ComPtr<IDXGIAdapter>> m_cpAdapters_V;	/// �׷���ī���
	std::vector<Microsoft::WRL::ComPtr<IDXGIOutput>> m_cpOutputs_V;		/// �����(ȭ��)

	std::vector<std::string> m_videoName_V;		// GPU�� �̸�(IDXGIAdapter DESC�� ���)
	std::vector<int> m_videoMemory_V;			// GPU �޸� ũ��(IDXGIAdapter DESC�� ���) : CPU�� �������� �ʴ� ���� ���� �޸��� ����Ʈ��
	std::vector<RECT> m_displayResolution_V;					// ȭ����� �ػ� (IDXGIOutput DESC�� ���)
	std::vector<std::vector<DXGI_MODE_DESC>> m_DXGIModes_V;		// ȭ���� ���÷��� ����(IDXGIOutput DESC�� ���)

	/// �� �� ������ �������� ������ ȭ��ũ�⳪ �ػ󵵸� �����Ҽ��ְ� �ҰŴ�(âȭ��, ��üȭ��)
	std::tuple<Microsoft::WRL::ComPtr<IDXGIAdapter>, std::vector<std::string>, std::vector<int> > a;
	std::tuple<Microsoft::WRL::ComPtr<IDXGIOutput>, std::vector<RECT>, std::vector<DXGI_MODE_DESC>> b;
};


/*
typedef struct DXGI_ADAPTER_DESC
{
	WCHAR  Description[128];        // ����� ����,
	UINT   VendorId;                // �ϵ���� ���޾�ü�� PCI ID
	UINT   DeviceId;                // �ϵ���� ��ġ�� PCI ID
	UINT   SubSysId;                // ����ý����� PCI ID
	UINT   Revision;                // ����� ����(revision) ��ȣ�� PCI ID
	SIZE_T DedicatedVideoMemory;    // CPU�� �������� ���� ���� ���� �޸��� ����Ʈ ��
	SIZE_T DedicatedSystemMemory;   // CPU�� �������� �ʴ� ���� �ý��� �޷θ� ����Ʈ ��
	SIZE_T SharedSystemMemory;      // ���� �ý��� �޸��� ����Ʈ ��
	LUID   AdapterLuid;             // ����͸� �ĺ��ϴ� ������(Locally Unique Identifier)
} DXGI_ADAPTER_DESC;
*/

/*
typedef struct DXGI_MODE_DESC {
  UINT                     Width;				// �ػ� ����
  UINT                     Height;				// �ػ� ����
  DXGI_RATIONAL            RefreshRate;			// �ֻ��� (Numerator ���� / Denominator �и�) 
  DXGI_FORMAT              Format;				// ���÷��� ����(DXGI_FORMAT_R32_UNIT ��)
  DXGI_MODE_SCANLINE_ORDER ScanlineOrdering;	// ��ĵ ��� : ���� �ּ�(���α׷��ú�) �Ǵ� ��� �ּ�(���ͷ��̽�) 
  DXGI_MODE_SCALING        Scaling;				// �ػ󵵿� �°� �̹����� �����ϸ� ó���� ��� ���� // ������ ����� ũ�⿡ �°� �ø��ų� ���̴� ���
} DXGI_MODE_DESC;
*/