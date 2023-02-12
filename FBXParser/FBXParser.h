#pragma once
#include <vector>

#include <fbxsdk.h>
#include <memory>

#include "ParsingData.h"
#include "MaterialData.h"

enum class eANIM_TYPE
{
	NONE = 0,	// �ִϸ��̼� ����
	SKINNED,	// ��Ű�� �ִϸ��̼�, ���̷��� + �ִϸ��̼��� �ִ�
	MESH,		// �ܼ� �޽� �ִϸ��̼�, no ���̷��� + �ִϸ��̼�
};

// �ļ� �ٱ����� ���������� ����ü
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
	/// ���� ����
	void SceneSetting(std::string& _fileName);

	/// ����� �Ӽ��� ���� �޽��� ���̷������� ����������.
	void LoadNode(fbxsdk::FbxNode* _node, FbxNodeAttribute::EType _attribute);

	void ProcessMesh(fbxsdk::FbxNode* _node);
	void ProcessSkeleton(fbxsdk::FbxNode* _node);

	void SetTransform(fbxsdk::FbxNode* _node, ParsingData::Bone* _bone);
	bool ProcessBoneWeights(fbxsdk::FbxNode* _node, std::vector<class BoneWeights>& _meshBoneWeights);
	
	/// Material ����(���������� �۾�)
	void LoadMaterial(std::vector<MaterialDesc>& _outMaterials);

	void GetMaterialTexture(fbxsdk::FbxSurfaceMaterial* _fbxSurMaterial, MaterialDesc& _outDesc);
	void LoadTextureProperty(fbxsdk::FbxProperty& _prop, MaterialDesc& _outDesc);
	void LoadTextureToMaterial(std::string _propertyName, fbxsdk::FbxFileTexture* _fileTexture, MaterialDesc& _outDesc);

	/// fbx ��Ʈ������ ����4 ���� �Լ�(���������� �۾�)
	DirectX::SimpleMath::Matrix ConvertMatrix(const FbxMatrix& _fbxMatrix);
	DirectX::SimpleMath::Vector4 ConvertVector4(const FbxVector4& _fbxVector4);

	DirectX::SimpleMath::Vector3 ConvertVector3(const FbxDouble3& _double3);
	float ConvertFloat(const FbxDouble& _fbxDouble);

	FbxAMatrix multT(FbxNode* _pNode);
	FbxVector4 multT(FbxNode* _pNode, FbxVector4 _fbxVector4);
	FbxAMatrix multTGeom(FbxNode* _pNode);

private:
	fbxsdk::FbxManager* m_pManager;							// Fbx sdk�� ������Ҹ� ����, �����ϴ� �Ŵ���
	fbxsdk::FbxScene* m_pScene;								// 3D��鿡 ���� ������ ������ ����(��Ʈ���, �ؽ��� ���)
	fbxsdk::FbxImporter* m_pImporter;						// Fbx ������ �о���̴� ��ü
	fbxsdk::FbxGeometryConverter* m_pGeometryConverter;		// ������ �ﰢ������ �����ִ� ������ �ϴ� ����

	fbxsdk::FbxString m_fbxFileName;						// �����̸�
	fbxsdk::FbxMesh* m_pFBXmesh;							// FBX�� �Ž�

	std::shared_ptr<FBXModel> m_pFBXModel;					// ���ϳ� ����
	
	std::shared_ptr<ParsingData::Mesh> m_pMesh;				// �ļ��� �Ž�
	std::unique_ptr<ParsingData::Skeleton> m_pSkeleton;
	std::vector<DirectX::SimpleMath::Matrix> m_BoneOffsets;

	bool m_HasSkeleton;

};

