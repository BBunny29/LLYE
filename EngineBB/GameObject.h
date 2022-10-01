#pragma once
#include <memory>

/// <summary>
/// ���� ������Ʈ
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

	/// ������Ʈ�� ���� 
	void OnEnable();
	void OnDisable();

	bool GetIsEnabled();
	bool GetIsContinualObject();

	/// �θ� �ڽ� ����
	void SetParent(GameObject* pObject);
	GameObject* GetParent() const;

	/// ������Ʈ
	const size_t GetComponentCnt();
	
	template <typename T>
	bool AddComponent(T* component);
	
	template <typename T>
	T* GetComponent();

	/// �±׿� �̸�
	void SetObjectName(const std::string& name);
	void SetTagName(const std::string& tag);		///���� �ܺο��� ����ϸ� �ȵȴ�! ���� ������Ʈ�Ŵ��������� ����ض�.
	const std::string& GetObjectName();
	const std::string& GetTag();

public:
	std::shared_ptr<class Transform> m_transform;
	std::vector<class Component*> m_Component_V;

private:
	bool m_bEnable;
	const bool m_bContinual;			// ���� �ٲ� �״�� �����Ұ�����

	std::string m_name;
	std::string m_tag;
	
	GameObject* m_pParent;
	std::vector <GameObject*> m_Children_V; // ���� ���������� ���Ͱ��Ƽ� �ӽ÷� ����

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
