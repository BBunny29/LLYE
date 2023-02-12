#include "pch.h"
#include "ComponentSystem.h"

#include "Component.h"
#include "ResourceObserverManager.h"

ComponentSystem::ComponentSystem()
{
}

ComponentSystem::~ComponentSystem()
{
}

void ComponentSystem::RegisterComponent(int type, Component* component)
{
	if (m_IsRunning == true)
	{
		m_TempRegisterComponent_V.push_back(std::make_pair(type, component));
		return;
	}

	RegisterComponent_NoOption(type, component);
}

void ComponentSystem::DeregisterComponent(GameObject* object)
{
}

void ComponentSystem::DeregisterComponent(int type, Component* component)
{
	m_IsRunning = false;

	DeregisterComponent_NoOption(type, component);
}

void ComponentSystem::RegisterComponent_NoOption(int type, Component* component)
{
	///2d vector ver
	///type번째 vector에 삽입한다.
	/// render component는 따로 관리
	if (type == static_cast<int>(ComponentType::Rendering))
	{
		m_RenderComponent_V.push_back(component);
	}
	else if (type == static_cast<int>(ComponentType::Camera))
	{
		//Managers::GetInstance()->GetCameraManager()->AddCamera(dynamic_cast<Camera*>(component), dynamic_cast<Camera*>(component)->GetName());
		m_Component_V.at(type).push_back(std::make_pair(type, component));
	}
	else
	{
		m_Component_V.at(type).push_back(std::make_pair(type, component));
	}

	//CA_TRACE("Component System : Register %u", component->GetComponetId());
}

void ComponentSystem::DeregisterComponent_NoOption(int type, Component* component)
{
	if (type == static_cast<int>(ComponentType::Rendering))
	{
		std::vector<Component*>::iterator _rCompV = m_RenderComponent_V.begin();
		for (; _rCompV != m_RenderComponent_V.end(); _rCompV++)
		{
			if (*_rCompV == component)
			{
				m_RenderComponent_V.erase(_rCompV);
				return;
			}
		}
	}
	std::vector<std::pair<int, Component*>>::iterator _pairVIter = m_Component_V.at(type).begin();

	for (; _pairVIter != m_Component_V.at(type).end(); _pairVIter++)
	{
		if (_pairVIter->second == component)
		{
			m_Component_V.at(type).erase(_pairVIter);
			return;
		}
	}

	DebugString::PDS("Component System : Deregister Fail");
}

void ComponentSystem::SetResourceManager(std::shared_ptr<IResourceManager> pResourceManager)
{
}

void ComponentSystem::Start()
{
	m_pResourceObserverOwner->Notify();

	std::vector<Component*>::iterator _rCompV = m_RenderComponent_V.begin();
	for (; _rCompV != m_RenderComponent_V.end(); _rCompV++)
	{
		(*_rCompV)->Start();
	}

	for (auto& _componentV : m_Component_V)
	{
		std::vector<std::pair<int, Component*>>::iterator _pairVIter = _componentV.begin();

		for (; _pairVIter != _componentV.end(); _pairVIter++)
		{
			if (_pairVIter->second->GetObjectIsExist())
			{
				_pairVIter->second->Start();
			}
			else
			{
				//스타트 시점에서 자신의 오브젝트가 없는 컴포넌트는 시스템에서 제외된다.
				//CA_TRACE("Component System : %u No Object", _pairVIter->second->GetComponetId());
				_componentV.erase(_pairVIter);
			}
		}
	}
}

void ComponentSystem::Update(float dTime)
{
	m_IsRunning = true;

	if (m_IsPaused == false)
	{

		std::vector<Component*>::iterator _rCompV = m_RenderComponent_V.begin();
		for (; _rCompV != m_RenderComponent_V.end(); _rCompV++)
		{
			(*_rCompV)->Update(dTime);
		}

		for (auto& _componentV : m_Component_V)
		{
			std::vector<std::pair<int, Component*>>::iterator _pairVIter = _componentV.begin();

			for (; _pairVIter != _componentV.end(); _pairVIter++)
			{
				if (_pairVIter->second->GetObjectIsEnabled())
				{
					if (_pairVIter->second->GetIsEnabled() == true)
					{			  
						_pairVIter->second->Update(dTime);
					}
				}
				else
				{
					//스타트 시점에서 자신의 오브젝트가 없는 컴포넌트는 시스템에서 제외된다.
					//CA_TRACE("Component System : %u No Object", _pairVIter->second->GetComponetId());
					_componentV.erase(_pairVIter);
				}
			}
		}
	}
}

void ComponentSystem::PreRender()
{
	for (Component*& _rComp : m_RenderComponent_V)
	{
		if (_rComp->GetObjectIsEnabled() == true)
		{
			if (_rComp->GetIsEnabled() == true)
			{
				_rComp->OnPreRender();
			}
		}
	}
}

void ComponentSystem::Render()
{
	for (Component*& _rComp : m_RenderComponent_V)
	{
		if (_rComp->GetObjectIsEnabled() == true)
		{
			if (_rComp->GetIsEnabled() == true)
			{
				_rComp->OnRender();
			}
		}
	}
}

void ComponentSystem::PostRender()
{
	for (Component*& _rComp : m_RenderComponent_V)
	{
		if (_rComp->GetObjectIsEnabled() == true)
		{
			if (_rComp->GetIsEnabled() == true)
			{
				_rComp->OnPostRender();
			}
		}
	}
}

void ComponentSystem::HelperRender()
{
	for (Component*& _rComp : m_RenderComponent_V)
	{
		if (_rComp->GetObjectIsEnabled() == true)
		{
			if (_rComp->GetIsEnabled() == true)
			{
				_rComp->OnHelperRender();
			}
		}
	}
}

void ComponentSystem::UIRender()
{
	for (Component*& _rComp : m_RenderComponent_V)
	{
		if (_rComp->GetObjectIsEnabled() == true)
		{
			if (_rComp->GetIsEnabled() == true)
			{
				_rComp->OnUIRender();
			}
		}
	}
}


