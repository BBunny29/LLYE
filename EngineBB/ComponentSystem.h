#pragma once

class Component;
class GameObject;

/// <summary>
/// ������Ʈ�� ������ �ô� Ŭ����
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
	std::vector<std::vector<std::pair<int, Component*>>> m_Component_V;		//������Ʈ�� ���ϴ� ������� �����ؾ� �Ѵ�, std::pair<type, ComponentBase*>
	std::vector<Component*> m_RenderComponent_V;
	std::vector<Component*> m_LightComponent_V;

	//std::shared_ptr<IResourceManager> m_pResourceManager;
	//ResourceLoader* m_pResourceLoader;
};

