#pragma once
#include <SimpleMath.h>
#include "Component.h"

class Transform : public Component
{
public:
	Transform();
	~Transform();

	virtual void Start() override;
	virtual void Update(float dTime) override;
	virtual void OnRender() override {}

public:
	/// Setter
	void SetPosition(const DirectX::SimpleMath::Vector3& pos);
	void SetPosition(const DirectX::XMVECTOR& pos);
	void SetPosition(float x, float y, float z);
	
	void SetRotation(const DirectX::SimpleMath::Vector3& rot);
	void SetRotation(const DirectX::XMVECTOR& rot);
	void SetRotation(const DirectX::SimpleMath::Quaternion& rotQ);
	void SetRotation(float x, float y, float z);
	
	void SetScale(float xScale, float yScale, float zScale = 1.0f);
	void SetScale(const DirectX::SimpleMath::Vector3& scl);

	/// Adjust
	void AdjustPosition(const DirectX::SimpleMath::Vector3& pos);
	void AdjustPosition(const DirectX::XMVECTOR& pos);
	void AdjustPosition(float x, float y, float z);

	void AdjustRotation(const DirectX::SimpleMath::Vector3& rot);
	void AdjustRotation(const DirectX::XMVECTOR& rot);
	void AdjustRotation(float x, float y, float z);

	/// Getter
	const DirectX::SimpleMath::Vector3& GetPos() const;
	const DirectX::XMVECTOR& GetPosXMVector() const;

	const DirectX::SimpleMath::Vector3& GetRot() const;
	const DirectX::XMVECTOR& GetRotXMVector() const;
	//const DirectX::SimpleMath::Quaternion& GetRotation() const;

	const DirectX::SimpleMath::Vector3& GetScale() const;


private:
	/// Sync
	void SyncPos();
	void SyncRot();
	void SyncRotQ();
	
	DirectX::SimpleMath::Quaternion EulerToQ(float xD, float yD, float zD);
	DirectX::SimpleMath::Vector3 QuaternionToEuler(DirectX::SimpleMath::Quaternion q1);
	DirectX::SimpleMath::Vector3 NormalizeAngles(DirectX::SimpleMath::Vector3 angles);
	float NormalizeAngle(float angle);

private:
	DirectX::SimpleMath::Vector3	m_pos;
	DirectX::XMVECTOR m_posXMVec;

	DirectX::SimpleMath::Vector3	m_rot;
	DirectX::XMVECTOR m_rotXMVec;
	DirectX::SimpleMath::Quaternion m_rotQ;
	
	DirectX::SimpleMath::Vector3	m_scale;

public:
	DirectX::SimpleMath::Matrix m_LocalTM;
	DirectX::SimpleMath::Matrix m_WorldTM;

	DirectX::SimpleMath::Matrix m_RotationTM; // 축회전 offset용 TM
};

