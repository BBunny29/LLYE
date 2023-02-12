#pragma once

class Component;
class GameObject;
class ResourceObserverManager;
__interface IResourceManager;

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
	
	/// 컴포넌트 등록
	void RegisterComponent(int type, Component* component);
	void DeregisterComponent(GameObject* object);
	void DeregisterComponent(int type, Component* component);

private:
	void RegisterComponent_NoOption(int type, Component* component);
	void DeregisterComponent_NoOption(int type, Component* component);

public:
	/// 리소스매니저
	void SetResourceManager(std::shared_ptr<IResourceManager> pResourceManager);

public:
	/// 루프
	void Start();
	void Update(float dTime);
	void PreRender();
	void Render();
	void PostRender();
	void HelperRender();
	void UIRender();

private:
	bool m_IsRunning; // 업데이트 중인지
	bool m_IsPaused;

	std::vector<std::vector<std::pair<int, Component*>>> m_Component_V;		//업데이트를 원하는 순서대로 삽입해야 한다, std::pair<type, ComponentBase*>
	std::vector<Component*> m_RenderComponent_V;
	//std::vector<Component*> m_LightComponent_V;

	//std::shared_ptr<IResourceManager> m_pResourceManager;
	//ResourceLoader* m_pResourceLoader;
	std::vector<std::pair<int, Component*>> m_TempRegisterComponent_V;		//업데이트중 생성/삽입된 컴포넌트를 임시로 보관하는 곳

	std::shared_ptr<ResourceObserverManager> m_pResourceObserverOwner;
	std::shared_ptr<IResourceManager> m_pResourceManager;

};

