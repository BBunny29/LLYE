#pragma once
#include <vector>

#include <fbxsdk.h>
#include <memory>

#include "ParsingData.h"
#include "MaterialData.h"

enum class eANIM_TYPE
{
	NONE = 0,	// 애니메이션 없음
	SKINNED,	// 스키닝 애니메이션, 스켈레톤 + 애니메이션이 있다
	MESH,		// 단순 메쉬 애니메이션, no 스켈레톤 + 애니메이션
};

// 파서 바깥으로 내보내지는 구조체
struct FBXModel
{
	std::string fileName;
	std::vector<std::string> materialName_V;
	std::vector<std::shared_ptr<ParsingData::Mesh>> pMesh_V;

	eANIM_TYPE animationType;

	bool isSkinnedAnimation;
	bool isMeshAnimation;

	//std::vector<std::shared_ptr<AnimationData>> pAnimation_V;
	std::unique_ptr<ParsingData::Skeleton> pSkeleton;
	std::vector<std::string> animationName_V;


	std::shared_ptr<ParsingData::Mesh> GetMesh(const std::string& name)
	{
		for (auto& nowMesh : pMesh_V)
		{
			if (name == nowMesh->nodeName)
			{
				return nowMesh;
			}
		}
		return nullptr;
	}
};

/// <summary>
/// 
/// </summary>
class FBXParser
{
public:
	FBXParser();
	~FBXParser();

	void Initalize();
	void Destroy();
	void LoadScene(std::string& _fileName, std::string& _writePath);

private:
	/// 기초 셋팅
	void SceneSetting(std::string& _fileName);

	/// 노드의 속성에 따라 메쉬와 스켈레론으로 나뉘어진다.
	void LoadNode(fbxsdk::FbxNode* _node, FbxNodeAttribute::EType _attribute);

	void ProcessMesh(fbxsdk::FbxNode* _node);
	void ProcessSkeleton(fbxsdk::FbxNode* _node);

	void SetTransform(fbxsdk::FbxNode* _node, ParsingData::Bone* _bone);
	bool ProcessBoneWeights(fbxsdk::FbxNode* _node, std::vector<class BoneWeights>& _meshBoneWeights);
	
	/// Material 관련(수종오빠의 작업)
	void LoadMaterial(std::vector<MaterialDesc>& _outMaterials);

	void GetMaterialTexture(fbxsdk::FbxSurfaceMaterial* _fbxSurMaterial, MaterialDesc& _outDesc);
	void LoadTextureProperty(fbxsdk::FbxProperty& _prop, MaterialDesc& _outDesc);
	void LoadTextureToMaterial(std::string _propertyName, fbxsdk::FbxFileTexture* _fileTexture, MaterialDesc& _outDesc);

	/// fbx 매트릭스와 벡터4 계산용 함수(수종오빠의 작업)
	DirectX::SimpleMath::Matrix ConvertMatrix(const FbxMatrix& _fbxMatrix);
	DirectX::SimpleMath::Vector4 ConvertVector4(const FbxVector4& _fbxVector4);

	DirectX::SimpleMath::Vector3 ConvertVector3(const FbxDouble3& _double3);
	float ConvertFloat(const FbxDouble& _fbxDouble);

	FbxAMatrix multT(FbxNode* _pNode);
	FbxVector4 multT(FbxNode* _pNode, FbxVector4 _fbxVector4);
	FbxAMatrix multTGeom(FbxNode* _pNode);

private:
	fbxsdk::FbxManager* m_pManager;							// Fbx sdk의 구성요소를 생성, 관리하는 매니저
	fbxsdk::FbxScene* m_pScene;								// 3D장면에 대한 정보를 가지고 있음(루트노드, 텍스쳐 등등)
	fbxsdk::FbxImporter* m_pImporter;						// Fbx 파일을 읽어들이는 객체
	fbxsdk::FbxGeometryConverter* m_pGeometryConverter;		// 모든면을 삼각형으로 나눠주는 역할을 하는 변수

	fbxsdk::FbxString m_fbxFileName;						// 파일이름
	fbxsdk::FbxMesh* m_pFBXmesh;							// FBX의 매쉬

	std::shared_ptr<FBXModel> m_pFBXModel;					// 모델하나 단위
	
	std::shared_ptr<ParsingData::Mesh> m_pMesh;				// 파서의 매쉬
	std::unique_ptr<ParsingData::Skeleton> m_pSkeleton;
	std::vector<DirectX::SimpleMath::Matrix> m_BoneOffsets;

	bool m_HasSkeleton;

};

