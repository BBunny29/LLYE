#pragma once
#include "DX11LibraryDefine.h"
#include "IRenderer.h"

class DX11Renderer : public IRenderer
{
public:
	DX11Renderer();
	~DX11Renderer();

	virtual bool Initialize(int hWnd, int screenWidth, int screenHeight) override;

	virtual void BeginRender() override;
	virtual void EndRender() override;
	virtual void Finalize() override;

public:
	virtual void Render() override;

private:
	// 이니셜라이즈용

private:
	HWND m_hWnd;
	unsigned int m_width = 0;
	unsigned int m_height = 0;

	/// 초기화 변수
	D3D_DRIVER_TYPE m_D3DDriverType;
	D3D_FEATURE_LEVEL m_eFeatureLevel;
	
	Microsoft::WRL::ComPtr<ID3D11Device> m_spDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_spDeviceContext;
	
	class AdapterData* m_pAdapterManager;


	///스마트 포인터 : 사용이 끝난 메모리를 자동으로 해제
	/*	GPU와 GPU의 자원의 virtual representation을 제공.
		주로 리소스( 버퍼나 텍스쳐 등 )의 생성에 대한 인터페이스 */

	//파이프라인에 대한 그래픽처리를 나타낸다
	//리소스를 제어하고 관리하기 위한 인터페이스
};
