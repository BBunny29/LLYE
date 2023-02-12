#include "pch.h"
#include "Camera.h"

#include <numbers>

#include "TransForm.h"
#include "Global_EngineBB.h"


Camera::Camera()
	: Component(ComponentType::Camera)
	, m_Right(1.0f, 0.0f, 0.0f)
	, m_Up(0.0f, 1.0f, 0.0f)
	, m_Look(0.0f, 0.0f, 1.0f)
{
	m_FovY = 0.25f * std::numbers::pi;
	m_Aspect = static_cast<float>(WINDOW::GetScreenWidth()) / static_cast<float>(WINDOW::GetScreenHeight());
	m_NearZ = 0.1f;
	m_FarZ = 1000.0f;
}

Camera::~Camera()
{
}

void Camera::Start()
{
}

void Camera::Update(float dTime)
{
	if (GetIsEnabled() == true)
	{
		UpdateViewMatrix();
	}
}

void Camera::UpdateViewMatrix()
{
	DirectX::SimpleMath::Vector3 _r = GetTransform()->m_WorldTM.Right();
	DirectX::SimpleMath::Vector3 _u = GetTransform()->m_WorldTM.Up();
	DirectX::SimpleMath::Vector3 _l = GetTransform()->m_WorldTM.Forward();
	DirectX::SimpleMath::Vector3 _p = GetTransform()->GetPos();// { m_Transform->m_WorldTM._41, m_Transform->m_WorldTM._42, m_Transform->m_WorldTM._43 };

	_l = DirectX::XMVector3Normalize(_l);
	_u = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(_l, _r));
	_r = DirectX::XMVector3Cross(_u, _l);

	float _x = - DirectX::XMVectorGetX(XMVector3Dot(_p, _r));
	float _y = - DirectX::XMVectorGetX(XMVector3Dot(_p, _u));
	float _z = - DirectX::XMVectorGetX(XMVector3Dot(_p, _l));

	m_Right = _r;
	m_Up = _u;
	m_Look = _l;

	m_View = DirectX::SimpleMath::Matrix(
		m_Right.x, m_Up.x, m_Look.x, 0.0f,
		m_Right.y, m_Up.y, m_Look.y, 0.0f,
		m_Right.z, m_Up.z, m_Look.z, 0.0f,
		_x, _y, _z, 1.0f);
}
