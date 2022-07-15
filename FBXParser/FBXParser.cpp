#include "FBXParser.h"


//fbxsdk::FbxManager* m_pManager = FbxManager::Create();
//fbxsdk::FbxScene* m_pScene = FbxScene::Create(m_pManager, "My Scene");
//
//// IOSettings 객체 생성 및 설정
//FbxIOSettings* ios = FbxIOSettings::Create(m_pManager, IOSROOT);
//m_pManager->SetIOSettings(ios);
//
//fbxsdk::FbxImporter* m_pImporter = FbxImporter::Create(m_pManager, "");
//
//fbxsdk::FbxGeometryConverter* m_pGeometryConverter;
//fbxsdk::FbxMesh* m_pFBXmesh;							// FBX의 매쉬
//fbxsdk::FbxString m_fbxFileName;						// 파일이름

FBXParser::FBXParser()
{
}

FBXParser::~FBXParser()
{
}

void FBXParser::Initalize()
{
	// FBX SDK Manager 생성
	m_pManager = FbxManager::Create();

	// Scene 생성
	m_pScene = FbxScene::Create(m_pManager, "My Scene");

	// IOSettings 객체 생성 및 설정(importer나 exporter용으로 설정해줄수 있다.)
	FbxIOSettings* ios = FbxIOSettings::Create(m_pManager, IOSROOT);
	m_pManager->SetIOSettings(ios);

	// FbxImporter 객체 생성
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

	// 로드가 불릴 때 마다 초기화 해준다
	m_pFBXModel = std::make_shared<FBXModel>();
	m_pFBXModel->fileName = fileName;

	SceneSetting();
}

void FBXParser::SceneSetting()
{
	// 씬 임포트
	// 여러개의 FBX를 한꺼번에 로드할때 문제가 발생한다.
	// m_pImporter를 리셋한다음에 다시 만들어야할까?
	
	// 하나의 Fbx파일을 로드할때마다(LoadScene) 임포터를 초기화하기로 했다.(2022.07.15)
	bool status = m_pImporter->Initialize(m_fbxFileName, -1, m_pManager->GetIOSettings());
	m_pImporter->Import(m_pScene);

	if (!status)
	{
		//CA_TRACE("Call to FbxImporter::Initialize() failed.\n");
		//CA_TRACE("Error returned: %s\n\n", m_pImporter->GetStatus().GetErrorString());

		exit(-1);
	}

	// 씬 내의 좌표축을 바꾼다. 
	FbxAxisSystem sceneAxisSystem = m_pScene->GetGlobalSettings().GetAxisSystem(); 
	FbxAxisSystem::MayaYUp.ConvertScene(m_pScene);

	// 씬 내에서 삼각형화 할 수 있는 모든 노드를 삼각형화 시킨다. 
	m_pGeometryConverter->Triangulate(m_pScene, true, true);
}
