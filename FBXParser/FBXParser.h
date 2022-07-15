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
	fbxsdk::FbxManager* m_pManager;							// Fbx sdk의 구성요소를 생성, 관리하는 매니저
	fbxsdk::FbxScene* m_pScene;								// 3ㅇ
	fbxsdk::FbxImporter* m_pImporter;						// 
	fbxsdk::FbxGeometryConverter* m_pGeometryConverter;
	fbxsdk::FbxMesh* m_pFBXmesh;							// FBX의 매쉬
	fbxsdk::FbxString m_fbxFileName;						// 파일이름

	//std::shared_ptr<FBXModel> m_pFBXModel;					// 모델하나 단위
	//std::shared_ptr<JMParserData::Mesh> m_pMesh;			// 파서의 매쉬
	//
	//std::unique_ptr<JMParserData::Skeleton> m_pSkeleton;
	//std::vector<DirectX::SimpleMath::Matrix> m_BoneOffsets;

	bool m_HasSkeleton;

	int indexDebug = 0;

};

