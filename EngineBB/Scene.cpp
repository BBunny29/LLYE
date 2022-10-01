#include "pch.h"
#include "Scene.h"

IScene::IScene()
	: m_SceneName()
	, m_sceneKind(eScene::None)
	, m_SceneIndex(0)
	, m_CurrentCamreaName("")
{
}

IScene::~IScene()
{
}

void IScene::SetName(std::string& name)
{
	m_SceneName = name;
}

std::string& IScene::GetSceneName()
{
	return m_SceneName;
}

void IScene::SetSceneIndex(const unsigned int idx)
{
	m_SceneIndex = idx;
}

const unsigned int IScene::GetSceneIndex()
{
	return m_SceneIndex;
}

void IScene::SetSceneKind(eScene sceneKind)
{
	m_sceneKind = sceneKind;
}

int IScene::GetSceneKind()
{
	return (int)m_sceneKind;
}

void IScene::AddObject(GameObject* gameobject)
{
	//m_pGameObjectManager->m_pGameObject_V.push_back(gameobject);
}

void IScene::ReleaseObject()
{
}

void IScene::ReleaseAllObject()
{
}
