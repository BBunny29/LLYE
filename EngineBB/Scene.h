#pragma once

class GameObject;

enum class eScene
{
	None = 0,
	GameScene,
};

/// <summary>
/// ������ �� Ŭ������ ��ӹ޾� �����δ�.
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
	std::shared_ptr<class ObjectManager> m_pGameObjectManager;	// ������ ������Ʈ�� �����ϴ� ��ü

protected:
	std::string m_SceneName;
	eScene m_sceneKind = eScene::None;
	
	unsigned int m_SceneIndex;
	std::string m_CurrentCamreaName;

};

