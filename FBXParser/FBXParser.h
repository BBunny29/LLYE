#pragma once
#include <fbxsdk.h>
#include <memory>
#include <vector>

#include "ParsingData.h"

// �ļ� �ٱ����� ���������� ����ü
struct FBXModel
{
	std::string fileName;
	std::vector<std::string> materialName_V;
	std::vector<std::shared_ptr<ParsingData::Mesh>> pMesh_V;

	// Parser���� Temp�� ������� Skeleton�� ����ϰ� �Ѱ��ֱ� ���� unique_ptr�� ���
	// unique_ptr�� �迭����, ���� �ÿ��� ���� �ٸ� ������� �����ؾ� �Ѵ�

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
	fbxsdk::FbxManager* m_pManager;							// Fbx sdk�� ������Ҹ� ����, �����ϴ� �Ŵ���
	fbxsdk::FbxScene* m_pScene;								// 3D��鿡 ���� ������ ������ ����(��Ʈ���, �ؽ��� ���)
	fbxsdk::FbxImporter* m_pImporter;						// Fbx ������ �о���̴� ��ü
	fbxsdk::FbxGeometryConverter* m_pGeometryConverter;		// 

	fbxsdk::FbxString m_fbxFileName;						// �����̸�
	fbxsdk::FbxMesh* m_pFBXmesh;							// FBX�� �Ž�

	std::shared_ptr<FBXModel> m_pFBXModel;					// ���ϳ� ����
	
	std::shared_ptr<ParsingData::Mesh> m_pMesh;			// �ļ��� �Ž�
	std::unique_ptr<ParsingData::Skeleton> m_pSkeleton;
	std::vector<DirectX::SimpleMath::Matrix> m_BoneOffsets;

	bool m_HasSkeleton;

};

