#pragma once
#include <SimpleMath.h>

class Transform
{
public:
	Transform();
	~Transform();

public:
	const DirectX::SimpleMath::Vector3& GetPositionFloat3() const;
	const DirectX::XMVECTOR& GetPositionVector() const;
	const DirectX::SimpleMath::Vector3& GetRotationFloat3() const;
	const DirectX::XMVECTOR& GetRotationVector() const;

	void SetPosition(const DirectX::SimpleMath::Vector3& pos);
	void SetPosition(const DirectX::XMVECTOR& pos);
	void SetPosition(float x, float y, float z);
	void AdjustPosition(const DirectX::SimpleMath::Vector3& pos);
	void AdjustPosition(const DirectX::XMVECTOR& pos);
	void AdjustPosition(float x, float y, float z);

	void SetRotation(const DirectX::SimpleMath::Vector3& rot);
	//void SetRotation(const DirectX::SimpleMath::Quaternion& rotQ);
	void SetRotation(const DirectX::XMVECTOR& rot);
	void SetRotation(float x, float y, float z);
	void AdjustRotation(const DirectX::SimpleMath::Vector3& rot);
	void AdjustRotation(const DirectX::XMVECTOR& rot);
	void AdjustRotation(float x, float y, float z);
	
	void SetScale(float xScale, float yScale, float zScale = 1.0f);

private:
	DirectX::SimpleMath::Vector3	m_pos;
	DirectX::SimpleMath::Vector3	m_rot;
	//DirectX::SimpleMath::Quaternion m_rotQ;
	DirectX::SimpleMath::Vector3	m_scale;

	DirectX::XMVECTOR m_posXMVec;
	DirectX::XMVECTOR m_rotXMVec;
	DirectX::XMVECTOR m_rotQXMVec;
};

