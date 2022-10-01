#include "pch.h"
#include "GameObject.h"
#include "Component.h"

GameObject::GameObject()
	: m_bEnable(true)
	, m_bContinual(false)
	, m_name("")
	, m_pParent(nullptr)
{
}

GameObject::GameObject(bool isContinual)
	: m_bEnable(true)
	, m_bContinual(isContinual)
	, m_name("")
	, m_pParent(nullptr)

{
}

GameObject::GameObject(std::string name, std::string tag, bool isContinual)
	: m_bEnable(true)
	, m_bContinual(isContinual)
	, m_name("")
	, m_pParent(nullptr)
{
}

GameObject::~GameObject()
{
}

void GameObject::Update(float dTime)
{
}

void GameObject::Finalize()
{
	/// 오브젝트 매니저에서 컴포넌트 등록해제를 해준후 컴포넌트들을 해제한다.
	if (m_bContinual == true)
	{

	}
	else
	{
		for (size_t _comp = 0; _comp < m_Component_V.size(); ++_comp)
		{
			m_Component_V.at(_comp)->Finalize();
			delete(m_Component_V.at(_comp));
		}
	}
}

void GameObject::Reset()
{
}

void GameObject::OnEnable()
{
	m_bEnable = true;
}

void GameObject::OnDisable()
{
	m_bEnable = false;
}

bool GameObject::GetIsEnabled()
{
	return m_bEnable;
}

bool GameObject::GetIsContinualObject()
{
	return m_bContinual;
}

void GameObject::SetParent(GameObject* pObject)
{
	m_pParent = pObject;
}

GameObject* GameObject::GetParent() const
{
	return m_pParent;
}

const size_t GameObject::GetComponentCnt()
{
	return m_Component_V.size();
}

void GameObject::SetObjectName(const std::string& name)
{
	m_name = name;
}

void GameObject::SetTagName(const std::string& tag)
{
	m_tag = tag;
}

const std::string& GameObject::GetObjectName()
{
	return m_name;
}

const std::string& GameObject::GetTag()
{
	return m_tag;
}


