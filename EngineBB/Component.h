#pragma once

class GameObject;

enum class ComponentType
{
	Rendering = -1,
	Light = -2,

	Camera = 1,
	Input,
	GameLogic,
	Etc,

	MeshFilter = 5,
	Animation,
	Particle,
};

/// <summary>
/// ������Ʈ Ŭ����
/// ������Ʈ���� �� Ŭ������ ��ӹ޴´�.
/// 
/// 2022. 09. 27 B.Bunny
/// </summary>
class Component
{
public:
	Component();
	Component(ComponentType type);
	virtual ~Component();

public:
	virtual void Update(float dTime) abstract;				

	virtual void OnPreRender();				// ��� ������Ʈ�� ��� ���� �ʿ䰡 ��� abstract�� �Ⱥ��� (RenderingŸ�Ը� ���ư����)
	virtual void OnRender() abstract;
	virtual void OnPostRender();
	virtual void OnHelperRender();
	virtual void OnUIRender();

	void Finalize();

	/// ������Ʈ�� ����
	virtual void OnEnable();
	virtual void OnDisable();
	void SetEnable(const bool& enalble);

	bool GetIsEnabled();
	const int GetComponentType();

	/// ������Ʈ�� ������ �ִ� ������Ʈ
	void SetMyObject(GameObject* object);
	bool GetObjectIsEnabled();
	bool GetObjectIsExist();
	GameObject* GetMyObject();

protected:
	class GameObject* m_pMyObject;			// �ڽ��� ����ִ� ������Ʈ�� �˾ƾ��� ��) physics���� transform �����Ҷ�

private:
	bool m_bEnable;
	const ComponentType m_Type;

};
