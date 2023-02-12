#pragma once

class GameObject;
class Transform;

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
/// 컴포넌트 클래스
/// 컴포넌트들은 이 클래스를 상속받는다.
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
	virtual void Start() abstract;				//Start는 Update 메서드가 처음 호출되기 직전, 스크립트가 활성화 되면 호출되어야 한다. 
	virtual void Update(float dTime) abstract;				

	virtual void OnPreRender();				// 모든 컴포넌트가 들고 있을 필요가 없어서 abstract를 안붙임 (Rendering타입만 돌아가면됨)
	virtual void OnRender() abstract;
	virtual void OnPostRender();
	virtual void OnHelperRender();
	virtual void OnUIRender();

	void Finalize();

	/// 컴포넌트의 상태
	virtual void OnEnable();
	virtual void OnDisable();
	void SetEnable(const bool& enalble);

	bool GetIsEnabled();
	const int GetComponentType();

	/// 컴포넌트를 가지고 있는 오브젝트
	void SetMyObject(GameObject* object);
	bool GetObjectIsEnabled();
	bool GetObjectIsExist();
	GameObject* GetMyObject();

	/// 트랜스폼
	Transform* GetTransform();

protected:
	class GameObject* m_pMyObject;			// 자신을 들고있는 오브젝트를 알아야함 예) physics에서 transform 접근할때

private:
	bool m_bEnable;
	const ComponentType m_Type;

	Transform* m_Transform;

};
