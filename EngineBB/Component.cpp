#include "pch.h"
#include "Component.h"
#include "GameObject.h"

Component::Component()
	: m_bEnable(true)
	, m_Type(ComponentType::Etc)
	, m_pMyObject(nullptr)
{
}

Component::Component(ComponentType type)
	: m_bEnable(true)
	, m_Type(type)
	, m_pMyObject(nullptr)
{
}

Component::~Component()
{
}

void Component::OnPreRender()
{
	// 아무것도 하지 않는다
}

void Component::OnPostRender()
{
	// 아무것도 하지 않는다
}

void Component::OnHelperRender()
{
	// 아무것도 하지 않는다
}

void Component::OnUIRender()
{
	// 아무것도 하지 않는다
}

void Component::Finalize()
{
}

void Component::OnEnable()
{
	m_bEnable = true;
}

void Component::OnDisable()
{
	m_bEnable = false;
}

void Component::SetEnable(const bool& enalble)
{
	m_bEnable = enalble;
}

bool Component::GetIsEnabled()
{
	return m_bEnable;
}

const int Component::GetComponentType()
{
	return static_cast<int>(m_Type);
}

void Component::SetMyObject(GameObject* object)
{
	m_pMyObject = object;
}

bool Component::GetObjectIsEnabled()
{
	return m_pMyObject->GetIsEnabled();
}

bool Component::GetObjectIsExist()
{
	return  (m_pMyObject != nullptr) ? true : false;;
}

GameObject* Component::GetMyObject()
{
	return m_pMyObject;
}

