#pragma once

class Component;
class GameObject;

/// <summary>
/// 컴포넌트의 관리를 맡는 클래스
/// 
/// 2022. 09. 27 B.Bunny
/// </summary>
class ComponentSystem : public Singleton<ComponentSystem>
{
public:
	ComponentSystem();
	~ComponentSystem();

	void RegisterComponent(int type, Component* component);
	void DeregisterComponent(GameObject* object);
	void DeregisterComponent(int type, Component* component);

private:
	void RegisterComponent_NoOption(int type, Component* component);
	void DeregisterComponent_NoOption(int type, Component* component);

private:
	std::vector<std::vector<std::pair<int, Component*>>> m_Component_V;		//업데이트를 원하는 순서대로 삽입해야 한다, std::pair<type, ComponentBase*>
	std::vector<Component*> m_RenderComponent_V;
	std::vector<Component*> m_LightComponent_V;

	//std::shared_ptr<IResourceManager> m_pResourceManager;
	//ResourceLoader* m_pResourceLoader;
};

