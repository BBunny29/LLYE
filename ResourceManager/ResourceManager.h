#pragma once
#include <memory>

#include "Interface_ResourceManager.h"

/// <summary>
/// ���ҽ��Ŵ���
/// ������ó�� ����� api(ex. DX11, DX12 ��...)�� ���� Ŭ������ ������ ������ �׷��ʿ���� api�� ���� ���ҽ��� ���� �������ְ� �Ϸ����Ѵ�
/// �ϴ� ������ ��������DX11�ۿ� ���� 
/// (DX11 ������� texture�� ���� ID3D11ShaderResourceView�� ������ �������������̴�.)
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

	/// ����̽��� ����̽� ���ؽ�Ʈ�� ���� ���鶧 �ʿ��� ����
	D3D_DRIVER_TYPE m_D3DDriverType;
	D3D_FEATURE_LEVEL m_eFeatureLevel;

	std::shared_ptr<class DX11MeshFactory> m_pMeshFactory;




};
