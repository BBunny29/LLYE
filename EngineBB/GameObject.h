#pragma once
#include <memory>

/// <summary>
/// 게임 오브젝트
/// 
/// 2022. 09. 27 B.Bunny
/// </summary>
class GameObject
{
public:
	GameObject();
	GameObject(bool isContinual);
	GameObject(std::string name, std::string tag, bool isContinual);

	virtual ~GameObject();

public:
	virtual void Update(float dTime);
	virtual void Finalize();
	virtual void Reset();

	/// 오브젝트의 상태 
	void OnEnable();
	void OnDisable();

	bool GetIsEnabled();
	bool GetIsContinualObject();

	/// 부모 자식 관계
	void SetParent(GameObject* pObject);
	GameObject* GetParent() const;

	/// 컴포넌트
	const size_t GetComponentCnt();
	
	template <typename T>
	bool AddComponent(T* component);
	
	template <typename T>
	T* GetComponent();

	/// 태그와 이름
	void SetObjectName(const std::string& name);
	void SetTagName(const std::string& tag);		///절대 외부에서 사용하면 안된다! 오직 오브젝트매니저에서만 사용해라.
	const std::string& GetObjectName();
	const std::string& GetTag();

public:
	std::shared_ptr<class Transform> m_transform;
	std::vector<class Component*> m_Component_V;

private:
	bool m_bEnable;
	const bool m_bContinual;			// 씬이 바뀌어도 그대로 존재할것인지

	std::string m_name;
	std::string m_tag;
	
	GameObject* m_pParent;
	std::vector <GameObject*> m_Children_V; // 추후 계층구조에 쓸것같아서 임시로 만듬

};

template<typename T>
inline bool GameObject::AddComponent(T* component)
{
	return false;
}

template<typename T>
inline T* GameObject::GetComponent()
{
	return nullptr;
}
