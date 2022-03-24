#pragma once
#include <SimpleMath.h>

class Transform
{
	Transform();
	~Transform();

	DirectX::SimpleMath::Vector3 m_pos;
	DirectX::SimpleMath::Vector3 m_rot;
	DirectX::SimpleMath::Quaternion m_scale;
};

