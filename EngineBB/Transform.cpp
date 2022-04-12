#include "pch.h"
#include "Transform.h"

Transform::Transform()
	: m_pos(DirectX::SimpleMath::Vector3())
	, m_rot(DirectX::SimpleMath::Vector3())
	//, m_rotQ(DirectX::SimpleMath::Quaternion())
	, m_scale(DirectX::SimpleMath::Vector3())
	, m_posXMVec(DirectX::XMVECTOR())
	, m_rotXMVec(DirectX::XMVECTOR())
	, m_rotQXMVec(DirectX::XMVECTOR())
{
}

Transform::~Transform()
{
}

const DirectX::SimpleMath::Vector3& Transform::GetPositionFloat3() const
{
	return this->m_pos;
}

const DirectX::XMVECTOR& Transform::GetPositionVector() const
{
	return this->m_posXMVec;
}

const DirectX::SimpleMath::Vector3& Transform::GetRotationFloat3() const
{
	return this->m_rot;
}

const DirectX::XMVECTOR& Transform::GetRotationVector() const
{
	return this->m_rotXMVec;
}

void Transform::SetPosition(const DirectX::SimpleMath::Vector3& pos)
{
	m_pos = pos;
	m_posXMVec = m_pos;
	//UpdateMatrix();
}
