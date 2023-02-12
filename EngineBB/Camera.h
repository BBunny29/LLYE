#pragma once
#include "simpleMath.h"

#include "Component.h"

class Camera : public Component
{
public: 
	Camera();
	~Camera();

	virtual void Start() override;
	virtual void Update(float dTime) override;
	virtual void OnRender() override {};

	DirectX::SimpleMath::Vector3 GetLook() const;
	DirectX::SimpleMath::Vector3 GetPosition() const;

	DirectX::SimpleMath::Matrix View() const;
	DirectX::SimpleMath::Matrix Proj() const;
	DirectX::SimpleMath::Matrix ViewProj() const;

	float GetNearZ() const;
	float GetFarZ() const;

private:
	void UpdateViewMatrix();

private:
	// 카메라의 상하좌우
	DirectX::SimpleMath::Vector3 m_Right;
	DirectX::SimpleMath::Vector3 m_Up;
	DirectX::SimpleMath::Vector3 m_Look;

	DirectX::SimpleMath::Matrix m_View;
	DirectX::SimpleMath::Matrix m_Proj;

	// for SetLens
	float m_NearZ;
	float m_FarZ;
	float m_Aspect;
	float m_FovY; // field of view
	float m_NearWndHeight;
	float m_FarWndHeight;

};

