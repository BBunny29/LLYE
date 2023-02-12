#pragma once
#include "DX11LibraryDefine.h"
#include "IRenderer.h"

/// <summary>
/// 렌더러
/// 
/// 2023.01.03 B.Bunny
/// </summary>
class DX11Renderer : public IRenderer
{
public:
	DX11Renderer();
	~DX11Renderer();

	virtual bool Initialize(int hWnd, int screenWidth, int screenHeight) override;
	virtual void Finalize() override;

	virtual void BeginRender() override;
	virtual void EndRender() override;
	virtual void Render() override;

	virtual void OnResize(int width, int height) override;

private:
	void CreateSwapChain();

public:
	/// Getter
	virtual HRESULT GetDeviceAndDeviceContext(void** device, void** deviceContext) override;

private:
	HWND m_hWnd;
	unsigned int m_width = 0;
	unsigned int m_height = 0;

	bool m_enable4xMsaa;

	/// 초기화 변수
	D3D_DRIVER_TYPE m_D3DDriverType;
	D3D_FEATURE_LEVEL m_eFeatureLevel;
	
	/// 디바이스와 디바이스 컨텍스트
	Microsoft::WRL::ComPtr<ID3D11Device> m_cpDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_cpDeviceContext;
	
	std::shared_ptr<class AdapterManager> m_spAdapterManager;
	
	//Front Buffer( 현재 화면에 보여지는 버퍼 )와 Back Buffer( 현재 연산을 해서 기록하는 버퍼 ) 를 준비해서 이것을 Flip 시키면서 번갈아 가면서 보여주는 것
	Microsoft::WRL::ComPtr<IDXGISwapChain1> m_cpSwapchain;

	std::shared_ptr<class Forward> m_Forward;

	///스마트 포인터 : 사용이 끝난 메모리를 자동으로 해제
	/*	GPU와 GPU의 자원의 virtual representation을 제공.
		주로 리소스( 버퍼나 텍스쳐 등 )의 생성에 대한 인터페이스 */

	//파이프라인에 대한 그래픽처리를 나타낸다
	//리소스를 제어하고 관리하기 위한 인터페이스
	std::shared_ptr<class Box> m_TestBox;

};
