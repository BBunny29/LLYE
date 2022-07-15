#pragma once
#include <fbxsdk.h>
#include <memory>
#include <vector>

// �ļ� �ٱ����� ���������� ����ü
struct FBXModel
{
	FBXModel();
	~FBXModel();

	std::string fileName;
	std::vector<std::string> materialName_V;
	std::vector<std::shared_ptr<JMParserData::Mesh>> pMesh_V;

	// Parser���� Temp�� ������� Skeleton�� ����ϰ� �Ѱ��ֱ� ���� unique_ptr�� ���
	// unique_ptr�� �迭����, ���� �ÿ��� ���� �ٸ� ������� �����ؾ� �Ѵ�

	std::unique_ptr<JMParserData::Skeleton> pSkeleton;
	std::vector<std::string> animationName_V;

	std::shared_ptr<JMParserData::Mesh> GetMesh(const std::string& name)
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

private:
	fbxsdk::FbxManager* m_pManager;							// Fbx sdk�� ������Ҹ� ����, �����ϴ� �Ŵ���
	fbxsdk::FbxScene* m_pScene;								// 3D��鿡 ���� ������ ������ ����(��Ʈ���, �ؽ��� ���)
	fbxsdk::FbxImporter* m_pImporter;						// Fbx ������ �о���̴� ��ü
	fbxsdk::FbxGeometryConverter* m_pGeometryConverter;		// 

	fbxsdk::FbxString m_fbxFileName;						// �����̸�
	fbxsdk::FbxMesh* m_pFBXmesh;							// FBX�� �Ž�

	std::shared_ptr<FBXModel> m_pFBXModel;					// ���ϳ� ����
	
	std::shared_ptr<JMParserData::Mesh> m_pMesh;			// �ļ��� �Ž�
	std::unique_ptr<JMParserData::Skeleton> m_pSkeleton;
	//std::vector<DirectX::SimpleMath::Matrix> m_BoneOffsets;

	bool m_HasSkeleton;

	int indexDebug = 0;

};

