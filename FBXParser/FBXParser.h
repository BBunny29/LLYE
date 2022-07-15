#pragma once
#include <fbxsdk.h>
#include <memory>

class FBXParser
{
public:
	FBXParser();
	~FBXParser();

	void Initalize();
	void Destroy();
	void LoadScene(std::string& fileName, std::string& writePath);

private:
	void SceneSetting();

private:
	fbxsdk::FbxManager* m_pManager;							// Fbx sdk�� ������Ҹ� ����, �����ϴ� �Ŵ���
	fbxsdk::FbxScene* m_pScene;								// 3��
	fbxsdk::FbxImporter* m_pImporter;						// 
	fbxsdk::FbxGeometryConverter* m_pGeometryConverter;
	fbxsdk::FbxMesh* m_pFBXmesh;							// FBX�� �Ž�
	fbxsdk::FbxString m_fbxFileName;						// �����̸�

	//std::shared_ptr<FBXModel> m_pFBXModel;					// ���ϳ� ����
	//std::shared_ptr<JMParserData::Mesh> m_pMesh;			// �ļ��� �Ž�
	//
	//std::unique_ptr<JMParserData::Skeleton> m_pSkeleton;
	//std::vector<DirectX::SimpleMath::Matrix> m_BoneOffsets;

	bool m_HasSkeleton;

	int indexDebug = 0;

};

