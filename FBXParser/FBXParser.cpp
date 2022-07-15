#include "FBXParser.h"


//fbxsdk::FbxManager* m_pManager = FbxManager::Create();
//fbxsdk::FbxScene* m_pScene = FbxScene::Create(m_pManager, "My Scene");
//
//// IOSettings ��ü ���� �� ����
//FbxIOSettings* ios = FbxIOSettings::Create(m_pManager, IOSROOT);
//m_pManager->SetIOSettings(ios);
//
//fbxsdk::FbxImporter* m_pImporter = FbxImporter::Create(m_pManager, "");
//
//fbxsdk::FbxGeometryConverter* m_pGeometryConverter;
//fbxsdk::FbxMesh* m_pFBXmesh;							// FBX�� �Ž�
//fbxsdk::FbxString m_fbxFileName;						// �����̸�

FBXParser::FBXParser()
{
}

FBXParser::~FBXParser()
{
}

void FBXParser::Initalize()
{
	// FBX SDK Manager ����
	m_pManager = FbxManager::Create();

	// Scene ����
	m_pScene = FbxScene::Create(m_pManager, "My Scene");

	// IOSettings ��ü ���� �� ����(importer�� exporter������ �������ټ� �ִ�.)
	FbxIOSettings* ios = FbxIOSettings::Create(m_pManager, IOSROOT);
	m_pManager->SetIOSettings(ios);

	// FbxImporter ��ü ����
	m_pImporter = FbxImporter::Create(m_pManager, "");

	m_pGeometryConverter = new FbxGeometryConverter(m_pManager);

}

void FBXParser::Destroy()
{
	m_pImporter->FbxImporter::Destroy();
	m_pScene->FbxScene::Destroy();
	m_pManager->FbxManager::Destroy();
}

void FBXParser::LoadScene(std::string& fileName, std::string& writePath)
{
	const char* _fileName = fileName.c_str();

	std::string _nowWritePath(writePath);
	_nowWritePath += StringHelper::GetFileName(fileName, false);

	m_fbxFileName = _fileName;
	m_HasSkeleton = false;

	// �ε尡 �Ҹ� �� ���� �ʱ�ȭ ���ش�
	m_pFBXModel = std::make_shared<FBXModel>();
	m_pFBXModel->fileName = fileName;

	SceneSetting();
}

void FBXParser::SceneSetting()
{
	// �� ����Ʈ
	// �������� FBX�� �Ѳ����� �ε��Ҷ� ������ �߻��Ѵ�.
	// m_pImporter�� �����Ѵ����� �ٽ� �������ұ�?
	
	// �ϳ��� Fbx������ �ε��Ҷ�����(LoadScene) �����͸� �ʱ�ȭ�ϱ�� �ߴ�.(2022.07.15)
	bool status = m_pImporter->Initialize(m_fbxFileName, -1, m_pManager->GetIOSettings());
	m_pImporter->Import(m_pScene);

	if (!status)
	{
		//CA_TRACE("Call to FbxImporter::Initialize() failed.\n");
		//CA_TRACE("Error returned: %s\n\n", m_pImporter->GetStatus().GetErrorString());

		exit(-1);
	}

	// �� ���� ��ǥ���� �ٲ۴�. 
	FbxAxisSystem sceneAxisSystem = m_pScene->GetGlobalSettings().GetAxisSystem(); 
	FbxAxisSystem::MayaYUp.ConvertScene(m_pScene);

	// �� ������ �ﰢ��ȭ �� �� �ִ� ��� ��带 �ﰢ��ȭ ��Ų��. 
	m_pGeometryConverter->Triangulate(m_pScene, true, true);
}
