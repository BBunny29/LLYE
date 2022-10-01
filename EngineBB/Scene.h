#pragma once

class GameObject;

enum class eScene
{
	None = 0,
	GameScene,
};

/// <summary>
/// 씬들은 이 클래스를 상속받아 움직인다.
/// 
/// 2022. 09. 29 B.Bunny
/// </summary>
class IScene
{
public:
	IScene();
	~IScene();

	virtual void Initialize() abstract;
	virtual void Update(float dTime) abstract;
	virtual void Reset() abstract;
	
	void SetName(std::string& name);
	std::string& GetSceneName();

	void SetSceneIndex(const unsigned int idx);
	const unsigned int GetSceneIndex();
	
	void SetSceneKind(eScene sceneKind);
	int GetSceneKind();

	//void StartComponent();
	void AddObject(GameObject* gameobject);
	void ReleaseObject();
	void ReleaseAllObject();
	
public:
	std::shared_ptr<class ObjectManager> m_pGameObjectManager;	// 씬에서 오브젝트를 관리하는 객체

protected:
	std::string m_SceneName;
	eScene m_sceneKind = eScene::None;
	
	unsigned int m_SceneIndex;
	std::string m_CurrentCamreaName;

};

