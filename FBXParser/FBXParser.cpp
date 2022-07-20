#include "pch.h"
#include "FBXParser.h"
#include "BoneWeights.h"
#include "StringHelper.h"
#include "DebugString.h"
#include <fbxsdk.h>

#define FBXSDK_SHARED

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

	// Scene에서 RootNode 가져오기..
	fbxsdk::FbxNode* _pRootNode = m_pScene->GetRootNode();

	//std::vector<MaterialDesc> _material_V;
	//// 머트리얼을 먼저 챙긴다
	//LoadMaterial(_material_V);

	// 노드 로드
	LoadNode(_pRootNode, FbxNodeAttribute::eSkeleton);
	if (m_HasSkeleton == true)
	{
		// 여기서 명확하게 판가름이 날것임
		m_BoneOffsets.resize(m_pSkeleton->m_Bones.size());
	}
	LoadNode(_pRootNode, FbxNodeAttribute::eMesh);
	//LoadAnimations();

	// m_pTempSkeleton에 대한 접근이 모두 끝나면 넘겨주자
	if (m_pSkeleton != nullptr)
	{
		m_pFBXModel->pSkeleton.swap(m_pSkeleton);
	}

	///시리얼라이저 
	//BinarySerializer* ser = new BinarySerializer();
	//ser->SaveBinaryFileFBX(m_pFBXModel.get(), _material_V, _nowWritePath.c_str());
	//ser->SaveAnimFile(m_pFBXModel.get(), _nowWritePath.c_str());

	//StopWatch::StopMeasure();

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
		DebugString::PDS("Call to FbxImporter::Initialize() failed.\n");
		DebugString::PDS("Error returned: %s\n\n", m_pImporter->GetStatus().GetErrorString());

		exit(-1);
	}

	// 씬 내의 좌표축을 바꾼다. 
	//fbxsdk::FbxAxisSystem sceneAxisSystem = m_pScene->GetGlobalSettings().GetAxisSystem();
	//fbxsdk::FbxAxisSystem::MayaYUp.ConvertScene(m_pScene);

	fbxsdk::FbxAxisSystem axisSystem(fbxsdk::FbxAxisSystem::eYAxis, fbxsdk::FbxAxisSystem::eParityOdd, fbxsdk::FbxAxisSystem::eRightHanded);
	fbxsdk::FbxAxisSystem sceneAxisSystem = m_pScene->GetGlobalSettings().GetAxisSystem();
	if (sceneAxisSystem != axisSystem)
	{
		axisSystem.ConvertScene(m_pScene);
	}

	//fbxsdk::FbxAxisSystem axis = fbxsdk::FbxAxisSystem::MayaYUp;
	//axis.ConvertScene(m_pScene);

	// 씬 내에서 삼각형화 할 수 있는 모든 노드를 삼각형화 시킨다. 
	m_pGeometryConverter->Triangulate(m_pScene, true, true);
}

void FBXParser::LoadNode(fbxsdk::FbxNode* node, FbxNodeAttribute::EType attribute)
{
	FbxNodeAttribute* _pNodeAtrribute = node->GetNodeAttribute();

	if (_pNodeAtrribute != nullptr)
	{
		FbxString nodename = node->GetName();
		FbxNodeAttribute::EType attributeType = _pNodeAtrribute->GetAttributeType();
		if (attributeType == attribute)
		{
			switch (_pNodeAtrribute->GetAttributeType())
			{
			case FbxNodeAttribute::eSkeleton:
				ProcessSkeleton(node);
				break;
			case FbxNodeAttribute::eMesh:
				ProcessMesh(node);
				break;
			case FbxNodeAttribute::eLight:
				break;
			default:
				break;
			}
		}
	}

	const unsigned int _childCount = node->GetChildCount();
	for (unsigned int i = 0; i < _childCount; i++)
	{
		// 자식 노드가 인덱싱되어있다는 사실을 알 수 있다
		std::string _name = node->GetName();
		LoadNode(node->GetChild(i), attribute);
	}
}

void FBXParser::ProcessMesh(fbxsdk::FbxNode* node)
{
	// 새로운 매쉬(m_pMesh) 생성
	m_pMesh = std::make_shared<ParsingData::Mesh>();
	m_pFBXModel->pMesh_V.push_back(m_pMesh);

	// 몇번째 인덱스인지 
	m_pMesh->meshIndex = m_pFBXModel->pMesh_V.size() - 1;
	m_pFBXmesh = node->GetMesh();

	// 머트리얼의 항상 첫번째 것을 가져온다 + 있으면 Mesh의 머트리얼 이름을 알려준다
	FbxSurfaceMaterial* _mat = node->GetMaterial(0);
	if (_mat != nullptr)
	{
		m_pFBXModel->materialName_V.push_back(_mat->GetName());
		m_pMesh->materialName = _mat->GetName();
	}

	m_pMesh->nodeName = node->GetName();

	//부모, 자식 노드 정보 저장
	if (node->GetParent() != nullptr)
	{
		m_pMesh->isParentExist = true;
		m_pMesh->nodeParentName = node->GetParent()->GetName();

		m_pMesh->pNodeParentMesh = m_pFBXModel->GetMesh(m_pMesh->nodeParentName);
		if (m_pMesh->pNodeParentMesh == nullptr)
		{
			m_pMesh->isParentExist = false;
		}
		if (m_pMesh->pNodeParentMesh != nullptr)
		{
			m_pMesh->pNodeParentMesh->childList_V.push_back(m_pMesh);
		}
	}
	else
	{
		m_pMesh->isParentExist = false;
	}

	// Node TRS 설정, Mesh만 있기 때문에 두번째 인자는 null만 넘겨준다
	SetTransform(node, nullptr);

	std::vector<BoneWeights> boneWeights;
	if (m_HasSkeleton == true)
	{
		// Vertex 개수만큼 BoneWeight 생성..
		// 해당 Vertex Index와 동일한 Index에 가중치 값, Bone Index Data 설정..
		boneWeights.resize(m_pFBXmesh->GetControlPointsCount());

		bool _isSkin = false;
		// Box처럼 Bone이 없는 구조도 생각하자
		_isSkin = ProcessBoneWeights(node, boneWeights);
		m_pMesh->isSkinningObject = true;
	}

	//CreateVertex(m_pFBXmesh, boneWeights, m_pFBXmesh->GetControlPointsCount());

	// Bone Data 설정 결과에 따른 Skinning Object 판별..
	/// 인덱스 정보 저장
	//m_pMesh->meshNumIndex = ProcessMeshVertexIndex();

	/// uv, 노말, 바이노말, 탄젠트값 추가
	//ProcessMeshVertexInfo();

	if (m_pSkeleton != nullptr)
	{
		m_pSkeleton->m_BoneOffsets = m_BoneOffsets;
	}

	/// 버텍스 스플릿
	//SplitMesh2();

	for (int i = 0; i < m_pMesh->meshFace_V.size(); i++)
	{
		//MakeTangentSpace(m_pFBXmesh, i);
	}

	for (int i = 0; i < m_pMesh->meshFace_V.size(); i++)
	{
		//MakeBinormal(i);
	}

	/// 버텍스 스플릿후 인덱스 정보 저장
	//?? 인덱스는 동일하게 주니까 안줘도 되나??
	unsigned int _optVertexCount = 0;

	// 버텍스 스플릿 후 인덱스 설정
	m_pMesh->pOptIndex = new ParsingData::IndexList[m_pMesh->meshFace_V.size() * 3];

	for (unsigned int i = 0; i < m_pMesh->meshFace_V.size(); i++)
	{
		ParsingData::Face* _nowFace = m_pMesh->meshFace_V[i];

		for (unsigned int j = 0; j < 3; j++)
		{
			switch (j)
			{
			case 0:
				m_pMesh->pOptIndex[i].index_A[j] = _nowFace->vertexIndex_A[0];
				break;
			case 1:
				m_pMesh->pOptIndex[i].index_A[j] = _nowFace->vertexIndex_A[2];
				break;
			case 2:
				m_pMesh->pOptIndex[i].index_A[j] = _nowFace->vertexIndex_A[1];
				break;
			default:
				break;
			}
		}
		//인덱스 개수를 센다
		_optVertexCount++;
	}

	m_pMesh->optIndexNum = _optVertexCount;
	//+ 각 버텍스마다 나눠줘야한다  
}

void FBXParser::ProcessSkeleton(fbxsdk::FbxNode* node)
{
	FbxSkeleton* fbxSkeleton = node->GetSkeleton();
	if (fbxSkeleton == nullptr) return;

	// 새로운 메쉬인지를 먼저 확인
	if (m_pSkeleton == nullptr)
	{
		m_pSkeleton = std::make_unique<ParsingData::Skeleton>();

		// 스켈레톤이 있다면 스키닝 애니메이션
		m_pFBXModel->isSkinnedAnimation = true;
		m_HasSkeleton = true;
	}

	ParsingData::Bone* _nowBone = new ParsingData::Bone();

	// 부모 Bone Index가 -1 이면 최상위 Root Node..
	// 최상위 노드(부모노드)인지 확인..
	int parentBoneIndex = -1;
	FbxNode* parentNode = node->GetParent();

	if (parentNode != nullptr)
	{
		std::string nodeName = parentNode->GetName();
		parentBoneIndex = m_pSkeleton->FindBoneIndex(nodeName);

		_nowBone->parentBoneName = node->GetParent()->GetName();
		_nowBone->isParentExist = true;

		if (0 <= parentBoneIndex)
		{
			_nowBone->pParentBone = m_pSkeleton->m_Bones[parentBoneIndex];
		}

		if (_nowBone->pParentBone != nullptr)
		{
			_nowBone->pParentBone->childBoneList_V.push_back(_nowBone);
		}
	}
	else
	{
		_nowBone->isParentExist = false;
	}

	_nowBone->boneName = node->GetName();
	_nowBone->parentBoneIndex = parentBoneIndex;
	m_pSkeleton->AddBone(_nowBone);

	// Node TRS 설정
	SetTransform(node, _nowBone);

	// 뼈대 없으면 return
	if (node->GetSkeleton() == nullptr)
	{
		return;
	}

	_nowBone->boneIndex = static_cast<int>(m_pSkeleton->m_Bones.size() - 1);	// 0번부터 시작하게 하려면
	_nowBone->isBoneSet = true;
	_nowBone->minmum = DirectX::SimpleMath::Vector3(+FLT_MAX, +FLT_MAX, +FLT_MAX);
	_nowBone->maximum = DirectX::SimpleMath::Vector3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
}

void FBXParser::SetTransform(fbxsdk::FbxNode* node, ParsingData::Bone* bone)
{
	if (node == nullptr) return;

	FbxMatrix _worldpos = m_pScene->GetAnimationEvaluator()->GetNodeGlobalTransform(node);
	FbxMatrix _localpos = m_pScene->GetAnimationEvaluator()->GetNodeLocalTransform(node);
	FbxMatrix _newMat = multT(node);
	FbxMatrix _newMatGeom = multTGeom(node);

	// 받아온 월드와 로컬TM을 뒤집어준다(yz축 방향 때문이라고 추측)
	DirectX::SimpleMath::Matrix _world = ConvertMatrix(_worldpos);
	DirectX::SimpleMath::Matrix _local = ConvertMatrix(_localpos);
	DirectX::SimpleMath::Matrix _newMat2 = ConvertMatrix(_newMat);
	DirectX::SimpleMath::Matrix _newMatGeom2 = ConvertMatrix(_newMatGeom);

	switch (node->GetNodeAttribute()->GetAttributeType())
	{
	case FbxNodeAttribute::eSkeleton:
	{
		// 루트 본만 처리해준다?
		if (bone->pParentBone == nullptr)
		{
			const auto yaw = -90.0f * DirectX::XM_PI / 180.0f;

			DirectX::SimpleMath::Quaternion q = DirectX::XMQuaternionRotationRollPitchYaw(yaw, 0.0f, 0.0f);

			_world *= XMMatrixRotationQuaternion(q);
			_local *= XMMatrixRotationQuaternion(q);
		}
		break;
	}

	//// 받아온 월드와 로컬TM을 뒤집어준다(yz축 방향 때문이라고 추측)
	//DirectX::SimpleMath::Matrix _world = AniConvertMatrix(_worldpos);
	//DirectX::SimpleMath::Matrix _local = AniConvertMatrix(_localpos);
	//
	//switch (node->GetNodeAttribute()->GetAttributeType())
	//{
	//case FbxNodeAttribute::eSkeleton:
	//{
	//	if (bone->pParentBone == nullptr)
	//	{
	//
	//	}
	//	break;
	//}

	case FbxNodeAttribute::eMesh:
	{
		if (m_pMesh->pNodeParentMesh == nullptr)
		{
			const auto yaw = -90.0f * DirectX::XM_PI / 180.0f;

			DirectX::SimpleMath::Quaternion q = DirectX::XMQuaternionRotationRollPitchYaw(yaw, 0.0f, 0.0f);

			_world *= XMMatrixRotationQuaternion(q);
			_local *= XMMatrixRotationQuaternion(q);
			_newMat2 *= XMMatrixRotationQuaternion(q);
			_newMatGeom2 *= XMMatrixRotationQuaternion(q);
		}
		break;
	}
	}

	DirectX::SimpleMath::Vector4 r1 = DirectX::SimpleMath::Vector4(_world._11, _world._12, _world._13, _world._14);
	DirectX::SimpleMath::Vector4 r2 = DirectX::SimpleMath::Vector4(_world._21, _world._22, _world._23, _world._24);
	DirectX::SimpleMath::Vector4 r3 = DirectX::SimpleMath::Vector4(_world._31, _world._32, _world._33, _world._34);
	DirectX::SimpleMath::Vector4 r4 = DirectX::SimpleMath::Vector4(_world._41, _world._42, _world._43, _world._44);

	//노드가 뼈대냐 매쉬냐에 따라 넣어주는곳 다름
	switch (node->GetNodeAttribute()->GetAttributeType())
	{
	case FbxNodeAttribute::eSkeleton:
	{
		bone->tmRow0 = DirectX::SimpleMath::Vector3(r1);
		bone->tmRow1 = DirectX::SimpleMath::Vector3(r2);
		bone->tmRow2 = DirectX::SimpleMath::Vector3(r3);
		bone->tmRow3 = DirectX::SimpleMath::Vector3(r4);

		bone->worldTM = _world;
		bone->localTM = _local;
		break;
	}
	case FbxNodeAttribute::eMesh:
	{
		m_pMesh->tmRow0 = DirectX::SimpleMath::Vector3(r1);
		m_pMesh->tmRow1 = DirectX::SimpleMath::Vector3(r2);
		m_pMesh->tmRow2 = DirectX::SimpleMath::Vector3(r3);
		m_pMesh->tmRow3 = DirectX::SimpleMath::Vector3(r4);

		if (m_pMesh->isParentExist == true)
		{
			m_pMesh->worldTM = DirectX::SimpleMath::Matrix();
			m_pMesh->localTM = _local;
		}
		else
		{
			m_pMesh->worldTM = _world;
			m_pMesh->localTM = DirectX::SimpleMath::Matrix();
		}
		break;
	}
	}
}

bool FBXParser::ProcessBoneWeights(fbxsdk::FbxNode* node, std::vector<BoneWeights>& meshBoneWeights)
{
	int deformerCount = m_pFBXmesh->GetDeformerCount();

	// DeformerCount가 1보다 작으면 Bone Data가 없다고 가정..
	if (deformerCount < 1) return false;

	// 스켈레톤-본의 size만큼 BoneAnimation을 Resize한다.


	for (int i = 0; i < deformerCount; ++i)
	{
		// Deform : 변형되다
		FbxDeformer* deformer = m_pFBXmesh->GetDeformer(i);

		if (deformer == nullptr) continue;

		if (deformer->GetDeformerType() == FbxDeformer::eSkin)
		{
			FbxSkin* skin = reinterpret_cast<FbxSkin*>(m_pFBXmesh->GetDeformer(i, FbxDeformer::eSkin));

			if (skin == nullptr) continue;

			// Cluster는 가중치를 가진 메쉬들의 부분집합이다
			// 스킨 안에 있는 모든 클러스트들의 개수
			int clusterCount = skin->GetClusterCount();

			FbxCluster::ELinkMode linkMode;

			// Skin Mesh 체크..
			//JMParserData::Mesh* skinMesh = FindMesh(node->GetName());
			std::vector<BoneWeights> skinBoneWeights(meshBoneWeights.size());
			for (int clusterIndex = 0; clusterIndex < clusterCount; clusterIndex++)
			{
				FbxCluster* cluster = skin->GetCluster(clusterIndex);
				if (cluster == nullptr) continue;
				linkMode = cluster->GetLinkMode();

				FbxNode* pLinkNode = cluster->GetLink();
				if (pLinkNode == nullptr) continue;
				std::string _currJointName = pLinkNode->GetName();

				// 현재 joint(본)의 이름을 통해 index를 구해온다
				int _boneIndex = m_pSkeleton->FindBoneIndex(_currJointName);
				if (_boneIndex < 0)
				{
					continue;
				}

				// Bone Index에 해당하는 Bone 추출..
				ParsingData::Bone* _nowBone = m_pSkeleton->m_Bones[_boneIndex];

				FbxAMatrix matClusterTransformMatrix;
				FbxAMatrix matClusterLinkTransformMatrix;

				cluster->GetTransformMatrix(matClusterTransformMatrix);
				cluster->GetTransformLinkMatrix(matClusterLinkTransformMatrix);

				// Bone Matrix 설정..
				DirectX::SimpleMath::Matrix clusterMatrix = ConvertMatrix(matClusterTransformMatrix);
				DirectX::SimpleMath::Matrix clusterlinkMatrix = ConvertMatrix(matClusterLinkTransformMatrix);

				_nowBone->bindPoseTransform = clusterlinkMatrix;
				_nowBone->boneReferenceTransform = clusterMatrix;

				// BindPose 행렬을 구하는 공식
				const FbxVector4 lT = node->GetGeometricTranslation(FbxNode::eDestinationPivot);
				const FbxVector4 lR = node->GetGeometricRotation(FbxNode::eDestinationPivot);
				const FbxVector4 lS = node->GetGeometricScaling(FbxNode::eDestinationPivot);

				FbxAMatrix geometryTransform = FbxAMatrix(lT, lR, lS);
				DirectX::SimpleMath::Matrix geometryMatrix = ConvertMatrix(geometryTransform);

				// OffsetMatrix는 WorldBindPose의 역행렬
				DirectX::SimpleMath::Matrix offsetMatrix = clusterMatrix * clusterlinkMatrix.Invert() * geometryMatrix;

				m_BoneOffsets[_boneIndex] = offsetMatrix;


				// Bone Mesh 체크..
				// 매트릭스랑 본의 index를 맞춰주기 위한 작업인듯

				for (int j = 0; j < cluster->GetControlPointIndicesCount(); ++j)
				{
					int index = cluster->GetControlPointIndices()[j];
					double weight = cluster->GetControlPointWeights()[j];

					skinBoneWeights[index].AddBoneWeight(_boneIndex, (float)weight);
				}
			}

			switch (linkMode)
			{
			case FbxCluster::eNormalize:
			{
				// 가중치 합을 1.0으로 만드는 작업..
				for (int i = 0; i < (int)skinBoneWeights.size(); ++i)
					skinBoneWeights[i].Normalize();
			}
			break;

			case FbxCluster::eAdditive:
				// 가중치가 몇이든 그냥 합산
				break;

			case FbxCluster::eTotalOne:
				// 이미 정규화가 되어있는 모드
				break;
			}

			for (size_t i = 0; i < meshBoneWeights.size(); i++)
				meshBoneWeights[i].AddBoneWeights(skinBoneWeights[i]);
		}
	}

	return true;
}




DirectX::SimpleMath::Matrix FBXParser::ConvertMatrix(FbxMatrix fbxMatrix)
{
	FbxVector4 r1 = fbxMatrix.GetRow(0);
	FbxVector4 r2 = fbxMatrix.GetRow(1);
	FbxVector4 r3 = fbxMatrix.GetRow(2);
	FbxVector4 r4 = fbxMatrix.GetRow(3);

	// 2행, 3행 변경..
	return DirectX::SimpleMath::Matrix
	(
		ConvertVector4(r1),
		ConvertVector4(r3),
		ConvertVector4(r2),
		ConvertVector4(r4)
	);
}

DirectX::SimpleMath::Vector4 FBXParser::ConvertVector4(FbxVector4 v4)
{
	// xyzw -> xzyw
	return DirectX::SimpleMath::Vector4
	(
		static_cast<float>(v4.mData[0]),
		static_cast<float>(v4.mData[2]),
		static_cast<float>(v4.mData[1]),
		static_cast<float>(v4.mData[3])
	);
}

FbxAMatrix FBXParser::multT(FbxNode* pNode)
{
	FbxAMatrix matrixGeo;
	matrixGeo.SetIdentity();
	if (pNode->GetNodeAttribute())
	{
		const FbxVector4 lT = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
		const FbxVector4 lR = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
		const FbxVector4 lS = pNode->GetGeometricScaling(FbxNode::eSourcePivot);
		matrixGeo.SetT(lT);
		matrixGeo.SetR(lR);
		matrixGeo.SetS(lS);
	}
	FbxAMatrix localMatrix = pNode->EvaluateLocalTransform();

	FbxNode* pParentNode = pNode->GetParent();
	FbxAMatrix parentMatrix = pParentNode->EvaluateLocalTransform();
	while ((pParentNode = pParentNode->GetParent()) != NULL)
	{
		parentMatrix = pParentNode->EvaluateLocalTransform() * parentMatrix;
	}

	FbxAMatrix matrix = parentMatrix * localMatrix * matrixGeo;
	//FbxVector4 result = matrix.MultT(vector);
	return matrix;
}

FbxVector4 FBXParser::multT(FbxNode* pNode, FbxVector4 vector)
{
	FbxAMatrix matrixGeo;
	matrixGeo.SetIdentity();
	if (pNode->GetNodeAttribute())
	{
		const FbxVector4 lT = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
		const FbxVector4 lR = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
		const FbxVector4 lS = pNode->GetGeometricScaling(FbxNode::eSourcePivot);
		matrixGeo.SetT(lT);
		matrixGeo.SetR(lR);
		matrixGeo.SetS(lS);
	}
	FbxAMatrix localMatrix = pNode->EvaluateLocalTransform();

	FbxNode* pParentNode = pNode->GetParent();
	FbxAMatrix parentMatrix = pParentNode->EvaluateLocalTransform();
	while ((pParentNode = pParentNode->GetParent()) != NULL)
	{
		parentMatrix = pParentNode->EvaluateLocalTransform() * parentMatrix;
	}

	FbxAMatrix matrix = parentMatrix * localMatrix * matrixGeo;
	FbxVector4 result = matrix.MultT(vector);
	return result;
}

FbxAMatrix FBXParser::multTGeom(FbxNode* pNode)
{
	FbxAMatrix matrixGeo;
	matrixGeo.SetIdentity();
	if (pNode->GetNodeAttribute())
	{
		const FbxVector4 lT = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
		const FbxVector4 lR = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
		const FbxVector4 lS = pNode->GetGeometricScaling(FbxNode::eSourcePivot);
		matrixGeo.SetT(lT);
		matrixGeo.SetR(lR);
		matrixGeo.SetS(lS);
	}
	FbxAMatrix localMatrix = pNode->EvaluateLocalTransform();

	FbxNode* pParentNode = pNode->GetParent();
	FbxAMatrix parentMatrix = pParentNode->EvaluateLocalTransform();
	while ((pParentNode = pParentNode->GetParent()) != NULL)
	{
		parentMatrix = pParentNode->EvaluateLocalTransform() * parentMatrix;
	}

	FbxAMatrix matrix = parentMatrix * localMatrix * matrixGeo;
	//FbxVector4 result = matrix.MultT(vector);
	return matrixGeo;
}
