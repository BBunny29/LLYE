#pragma once

class Component;
class GameObject;
class ResourceObserverManager;
__interface IResourceManager;

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
	
	/// ������Ʈ ���
	void RegisterComponent(int type, Component* component);
	void DeregisterComponent(GameObject* object);
	void DeregisterComponent(int type, Component* component);

private:
	void RegisterComponent_NoOption(int type, Component* component);
	void DeregisterComponent_NoOption(int type, Component* component);

public:
	/// ���ҽ��Ŵ���
	void SetResourceManager(std::shared_ptr<IResourceManager> pResourceManager);

public:
	/// ����
	void Start();
	void Update(float dTime);
	void PreRender();
	void Render();
	void PostRender();
	void HelperRender();
	void UIRender();

private:
	bool m_IsRunning; // ������Ʈ ������
	bool m_IsPaused;

	std::vector<std::vector<std::pair<int, Component*>>> m_Component_V;		//������Ʈ�� ���ϴ� ������� �����ؾ� �Ѵ�, std::pair<type, ComponentBase*>
	std::vector<Component*> m_RenderComponent_V;
	//std::vector<Component*> m_LightComponent_V;

	//std::shared_ptr<IResourceManager> m_pResourceManager;
	//ResourceLoader* m_pResourceLoader;
	std::vector<std::pair<int, Component*>> m_TempRegisterComponent_V;		//������Ʈ�� ����/���Ե� ������Ʈ�� �ӽ÷� �����ϴ� ��

	std::shared_ptr<ResourceObserverManager> m_pResourceObserverOwner;
	std::shared_ptr<IResourceManager> m_pResourceManager;

};

