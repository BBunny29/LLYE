#pragma once
#include <memory>

#include "Interface_ResourceManager.h"

/// <summary>
/// 리소스매니저
/// 런더러처럼 사용한 api(ex. DX11, DX12 등...)에 따라 클래스를 나눌까 했지만 그럴필요없이 api에 따른 리소스를 전부 가지고있게 하려고한다
/// 일단 지금은 렌더러가DX11밖에 없고 
/// (DX11 같은경우 texture를 위한 ID3D11ShaderResourceView를 변수로 가지고있을것이다.)
/// 
/// 2022.10.17 B.Bunny
/// </summary>
class ResourceManager : public IResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

public:
	virtual bool Initialize(std::shared_ptr<IRenderer> pRenderer) override;

	virtual int GetInfo() override;

private:
	std::shared_ptr<IRenderer> m_pRenderer;
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;

	/// 디바이스와 디바이스 컨텍스트를 직접 만들때 필요한 변수
	D3D_DRIVER_TYPE m_D3DDriverType;
	D3D_FEATURE_LEVEL m_eFeatureLevel;

	std::shared_ptr<class DX11MeshFactory> m_pMeshFactory;




};
