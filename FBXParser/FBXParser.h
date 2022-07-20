#pragma once
#include <fbxsdk.h>
#include <memory>
#include <vector>

#include "ParsingData.h"

// 파서 바깥으로 내보내지는 구조체
struct FBXModel
{
	std::string fileName;
	std::vector<std::string> materialName_V;
	std::vector<std::shared_ptr<ParsingData::Mesh>> pMesh_V;

	// Parser에서 Temp로 만들어진 Skeleton을 깔끔하게 넘겨주기 위해 unique_ptr을 썼다
	// unique_ptr의 배열형태, 생성 시에도 전혀 다른 방법으로 생성해야 한다

	std::unique_ptr<ParsingData::Skeleton> pSkeleton;
	std::vector<std::string> animationName_V;

	bool isSkinnedAnimation;

	std::shared_ptr<ParsingData::Mesh> GetMesh(const std::string& name)
	{
		for (auto& _nowMesh : pMesh_V)
		{
			if (name == _nowMesh->nodeName)
			{
				return _nowMesh;
			}
		}
		return nullptr;
	}
};

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

	void LoadNode(fbxsdk::FbxNode* node, FbxNodeAttribute::EType attribute);

	void ProcessMesh(fbxsdk::FbxNode* node);
	void ProcessSkeleton(fbxsdk::FbxNode* node);

	bool ProcessBoneWeights(fbxsdk::FbxNode* node, std::vector<class BoneWeights>& meshBoneWeights);
	void SetTransform(fbxsdk::FbxNode* node, ParsingData::Bone* bone);

	DirectX::SimpleMath::Matrix ConvertMatrix(FbxMatrix fbxMatrix);
	DirectX::SimpleMath::Vector4 ConvertVector4(FbxVector4 v4);

	FbxAMatrix multT(FbxNode* pNode);
	FbxVector4 multT(FbxNode* pNode, FbxVector4 vector);
	FbxAMatrix multTGeom(FbxNode* pNode);

private:
	fbxsdk::FbxManager* m_pManager;							// Fbx sdk의 구성요소를 생성, 관리하는 매니저
	fbxsdk::FbxScene* m_pScene;								// 3D장면에 대한 정보를 가지고 있음(루트노드, 텍스쳐 등등)
	fbxsdk::FbxImporter* m_pImporter;						// Fbx 파일을 읽어들이는 객체
	fbxsdk::FbxGeometryConverter* m_pGeometryConverter;		// 

	fbxsdk::FbxString m_fbxFileName;						// 파일이름
	fbxsdk::FbxMesh* m_pFBXmesh;							// FBX의 매쉬

	std::shared_ptr<FBXModel> m_pFBXModel;					// 모델하나 단위
	
	std::shared_ptr<ParsingData::Mesh> m_pMesh;			// 파서의 매쉬
	std::unique_ptr<ParsingData::Skeleton> m_pSkeleton;
	std::vector<DirectX::SimpleMath::Matrix> m_BoneOffsets;

	bool m_HasSkeleton;

};

