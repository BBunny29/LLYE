/// <summary>
/// �����(GPU) ������ ������ �ִ� Ŭ����
/// ID3D11Device, ID3D11DeviceContext, IDXGISwapChain�� �����ϱ����� �ʿ��ϴ�
/// 2021. 12. 02 BB
/// </summary>

#pragma once
#include <vector>
#include "DX11Define.h"

class AdapterData
{
public:
	AdapterData();
	AdapterData(Microsoft::WRL::ComPtr<IDXGIAdapter> pAdapter);
	~AdapterData();

	void Initialize(Microsoft::WRL::ComPtr<ID3D11Device> pDevice);

private:
	Microsoft::WRL::ComPtr<IDXGIAdapter> m_spAdapter = nullptr;
	Microsoft::WRL::ComPtr<IDXGIOutput> m_spOutput = nullptr;
	std::vector<DXGI_MODE_DESC*> m_DXGIMode_V;
	
	// IDXGIAdapter :
	// ��ǻ���� �ϵ���� �� ����Ʈ���� ����� �߻�ȭ�� ���Դϴ�. 
	// �ٸ� ����, �ϳ� �̻��� GPU, DAC, ���� �޸𸮸� �����ϴ� ���÷��� ����ý����� ǥ���մϴ�
	
	Microsoft::WRL::ComPtr<IDXGIFactory2> m_DXGIFactory = nullptr;

	DXGI_ADAPTER_DESC m_description;	// �׷���ī�� ����
		// ����ü���� ���鶧�� ���Ǵ� ���丮
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

};

//class AdapterReader
//{
//public:
//	static std::vector<AdapterData> GetAdapters();
//
//private:
//	//vector�� �޴� ���� : �������� ������(GPU)�� ���� �� �ֱ� ����
//	static std::vector<AdapterData> m_adapter_V;
//};

