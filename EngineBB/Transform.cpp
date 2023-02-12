#include "pch.h"
#include "Transform.h"

#include <numbers>

Transform::Transform()
	: m_pos(DirectX::SimpleMath::Vector3())
	, m_posXMVec(DirectX::XMVECTOR())
	, m_rot(DirectX::SimpleMath::Vector3())
	, m_rotXMVec(DirectX::XMVECTOR())
	, m_rotQ(DirectX::SimpleMath::Quaternion())
	, m_scale(DirectX::SimpleMath::Vector3())
{
}

Transform::~Transform()
{
}

void Transform::Start()
{
}

void Transform::Update(float dTime)
{
}

/// ----------------------------------------------
///  Setter
/// ----------------------------------------------
void Transform::SetPosition(const DirectX::SimpleMath::Vector3& pos)
{
	m_pos = pos;

	SyncPos();
}

void Transform::SetPosition(const DirectX::XMVECTOR& pos)
{
	m_pos = pos;

	SyncPos();
}

void Transform::SetPosition(float x, float y, float z)
{
	m_pos.x = x;
	m_pos.y = y; 
	m_pos.z = z;

	SyncPos();
}

void Transform::SetRotation(const DirectX::SimpleMath::Vector3& rot)
{
	m_rot = rot;

	SyncRot();
}

void Transform::SetRotation(const DirectX::XMVECTOR& rot)
{
	m_rot = rot;
	SyncRot();
}

void Transform::SetRotation(const DirectX::SimpleMath::Quaternion& rotQ)
{
	m_rotQ = rotQ;

}

void Transform::SetRotation(float x, float y, float z)
{
	m_rot.x = x;
	m_rot.y = y;
	m_rot.z = z;

	SyncRot();
}

void Transform::SetScale(float xScale, float yScale, float zScale)
{
	m_scale.x = xScale;
	m_scale.y = yScale;
	m_scale.z = zScale;
}

void Transform::SetScale(const DirectX::SimpleMath::Vector3& scl)
{
	m_scale = scl;
}

/// ----------------------------------------------
/// Adjust
/// ----------------------------------------------
void Transform::AdjustPosition(const DirectX::SimpleMath::Vector3& pos)
{
	m_pos += pos;

	SyncPos();
}

void Transform::AdjustPosition(const DirectX::XMVECTOR& pos)
{
	m_pos += pos;

	SyncPos();
}

void Transform::AdjustPosition(float x, float y, float z)
{
	m_pos.x += x;
	m_pos.y += y;
	m_pos.z += z;

	SyncPos();
}

void Transform::AdjustRotation(const DirectX::SimpleMath::Vector3& rot)
{
	DirectX::SimpleMath::Vector3 value = NormalizeAngles(rot);	// 0 ~ 360 사이로 제한
	m_rot += value;	

	SyncRot();
}

void Transform::AdjustRotation(const DirectX::XMVECTOR& rot)
{
	DirectX::SimpleMath::Vector3 value = NormalizeAngles(rot);	// 0 ~ 360 사이로 제한
	m_rot += value;

	SyncRot();
}

void Transform::AdjustRotation(float x, float y, float z)
{
	DirectX::SimpleMath::Vector3 value = NormalizeAngles(DirectX::SimpleMath::Vector3(x, y, z));	// 0 ~ 360 사이로 제한
	m_rot += value;

	SyncRot();
}

/// ----------------------------------------------
///  Getter
/// ----------------------------------------------
const DirectX::SimpleMath::Vector3& Transform::GetPos() const
{
	return m_pos;
}

const DirectX::XMVECTOR& Transform::GetPosXMVector() const
{
	return m_posXMVec;
}

const DirectX::SimpleMath::Vector3& Transform::GetRot() const
{
	return m_rot;
}

const DirectX::XMVECTOR& Transform::GetRotXMVector() const
{
	return m_rotXMVec;
}

const DirectX::SimpleMath::Vector3& Transform::GetScale() const
{
	return m_scale;
}

/// ----------------------------------------------
///  Sync
/// ----------------------------------------------
void Transform::SyncPos()
{
	m_posXMVec = m_pos;
}

void Transform::SyncRot()
{
	m_rotXMVec = m_rot;

	// Degree -> Radian
	float _radianX = m_rot.x * std::numbers::pi / 180;
	float _radianY = m_rot.y * std::numbers::pi / 180;
	float _radianZ = m_rot.z * std::numbers::pi / 180;

	// 쿼터니언을 만들고 계산된 쿼터니언으로 매트릭스를 세팅
	m_rotQ = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(_radianY, _radianX, _radianZ);
	m_RotationTM = DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_rotQ);
}

void Transform::SyncRotQ()
{
	m_RotationTM = DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_rotQ);

	// 쿼터니언 -> 오일러
	float a;
	DirectX::XMQuaternionToAxisAngle(&m_rotXMVec, &a, m_rotQ);
	m_rot = m_rotXMVec;
}

DirectX::SimpleMath::Quaternion Transform::EulerToQ(float xD, float yD, float zD)
{
	//라디안으로 변환
	// 라디안 = degree * (pi / 180)
	//yaw
	xD *= (std::numbers::pi / 180);
	// pitch
	yD *= (std::numbers::pi / 180);
	// roll
	zD *= (std::numbers::pi / 180);

	float yawOver2 = xD * 0.5f;
	float sinYawOver2 = (float)sinf((double)yawOver2);
	float cosYawOver2 = (float)cosf((double)yawOver2);

	float pitchOver2 = yD * 0.5f;
	float sinPitchOver2 = (float)sinf((double)pitchOver2);
	float cosPitchOver2 = (float)cosf((double)pitchOver2);

	float rollOver2 = zD * 0.5f;
	float sinRollOver2 = (float)sinf((double)rollOver2);
	float cosRollOver2 = (float)cosf((double)rollOver2);

	DirectX::SimpleMath::Quaternion result;
	result.w = cosYawOver2 * cosPitchOver2 * cosRollOver2 + sinYawOver2 * sinPitchOver2 * sinRollOver2;
	result.x = cosYawOver2 * sinPitchOver2 * cosRollOver2 + sinYawOver2 * cosPitchOver2 * sinRollOver2;
	result.y = sinYawOver2 * cosPitchOver2 * cosRollOver2 - cosYawOver2 * sinPitchOver2 * sinRollOver2;
	result.z = cosYawOver2 * cosPitchOver2 * sinRollOver2 - sinYawOver2 * sinPitchOver2 * cosRollOver2;

	return result;
}

DirectX::SimpleMath::Vector3 Transform::QuaternionToEuler(DirectX::SimpleMath::Quaternion q1)
{
	float sqw = q1.w * q1.w;
	float sqx = q1.x * q1.x;
	float sqy = q1.y * q1.y;
	float sqz = q1.z * q1.z;

	float unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor

	float test = q1.x * q1.w - q1.y * q1.z;

	DirectX::SimpleMath::Vector3 v;

	if (test > 0.4995f * unit) { // singularity at north pole

		v.y = 2 * atan2(q1.y, q1.x);
		v.x = std::numbers::pi / 2;
		v.z = 0;

		return NormalizeAngles(v * (180 / std::numbers::pi));
	}

	if (test < -0.4995f * unit) { // singularity at south pole

		v.y = -2 * atan2(q1.y, q1.x);
		v.x = -std::numbers::pi / 2;
		v.z = 0;

		return NormalizeAngles(v * (180 / std::numbers::pi));
	}

	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion(q1.w, q1.z, q1.x, q1.y);

	v.y = (float)atan2(2 * q.x * q.w + 2 * q.y * q.z, 1 - 2 * (q.z * q.z + q.w * q.w));	// Yaw
	v.x = (float)asin(2 * (q.x * q.z - q.w * q.y));											// Pitch
	v.z = (float)atan2(2 * q.x * q.y + 2 * q.z * q.w, 1 - 2 * (q.y * q.y + q.z * q.z));  // Roll

	return NormalizeAngles(v * (180 / std::numbers::pi));
}

DirectX::SimpleMath::Vector3 Transform::NormalizeAngles(DirectX::SimpleMath::Vector3 angles)
{
	angles.x = NormalizeAngle(angles.x);
	angles.y = NormalizeAngle(angles.y);
	angles.z = NormalizeAngle(angles.z);

	return angles;
}

float Transform::NormalizeAngle(float angle)
{
	while (angle > 360)
	{
		angle -= 360;
	}

	while (angle < 0)
	{
		angle += 360;
	}

	return angle;
}