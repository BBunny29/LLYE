#include "pch.h"
#include "FBXParser.h"

#include <iostream>
#include <fbxsdk.h>

#include "BoneWeights.h"
#include "AnimationData.h"
#include "MaterialData.h"
#include "StringHelper.h"
#include "DebugString.h"
#include "FBXModelSerializer.h"

//#define FBXSDK_SHARED

FBXParser::FBXParser()
	: m_pManager()
	, m_pScene()
	, m_pImporter()
	, m_pGeometryConverter()
	, m_fbxFileName()
	, m_pFBXmesh()
	, m_pFBXModel()
	, m_pMesh()
	, m_pSkeleton()
	, m_BoneOffsets()
	, m_HasSkeleton(false)
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

void FBXParser::LoadScene(std::string& _fileName, std::string& _writePath)
{
	const char* fileName = _fileName.c_str();

	std::string nowWritePath(_writePath);

	nowWritePath += StringHelper::GetFileName(_fileName, false);

	m_fbxFileName = fileName;
	m_HasSkeleton = false;

	// �ε尡 �Ҹ� �� ���� �ʱ�ȭ ���ش�
	m_pFBXModel = std::make_shared<FBXModel>();
	m_pFBXModel->fileName = fileName;

	SceneSetting(_fileName);

	// Scene���� RootNode ��������..
	fbxsdk::FbxNode* pRootNode = m_pScene->GetRootNode();

	// ��Ʈ������ ���� ì���
	std::vector<MaterialDesc> material_V;
	LoadMaterial(material_V);

	// ��� �ε�
	LoadNode(pRootNode, FbxNodeAttribute::eSkeleton);
	if (m_HasSkeleton == true)
	{
		m_BoneOffsets.resize(m_pSkeleton->m_Bones.size());
	}
	LoadNode(pRootNode, FbxNodeAttribute::eMesh);
	
	//LoadAnimations();

	// m_pTempSkeleton�� ���� ������ ��� ������ �Ѱ�����
	if (m_pSkeleton != nullptr)
	{
		m_pFBXModel->pSkeleton.swap(m_pSkeleton);
	}

	/// �ø��������
	// �ϳ��� fbx������ �Ľ��ϸ� �ø���������Ѵ�
	FBXModelSerializer* fbxModelSerializer = new FBXModelSerializer();
	fbxModelSerializer->SaveBinaryFileFBX(m_pFBXModel.get(), material_V, nowWritePath.c_str());
	//fbxModelSerializer->SaveAnimFile(m_pFBXModel.get(), _nowWritePath.c_str());

}

void FBXParser::SceneSetting(std::string& _fileName)
{
	// �� ����Ʈ
	// �������� FBX�� �Ѳ����� �ε��Ҷ� ������ �߻��Ѵ�.
	// m_pImporter�� �����Ѵ����� �ٽ� �������ұ�?

	// �ϳ��� Fbx������ �ε��Ҷ�����(LoadScene) �����͸� �ʱ�ȭ�ϱ�� �ߴ�.(2022.07.15)
	bool status = m_pImporter->Initialize(m_fbxFileName, -1, m_pManager->GetIOSettings());
	m_pImporter->Import(m_pScene);

	if (!status)
	{
		std::cout << "fail" << std::endl;
		DebugString::PDS("Call to FbxImporter::Initialize() failed.\n");
		DebugString::PDS("Error returned: %s\n\n", m_pImporter->GetStatus().GetErrorString());

		exit(-1);
	}

	std::cout << "SceneSetting Success : " << _fileName << std::endl;

	// �� ���� ��ǥ���� �ٲ۴�. 
	fbxsdk::FbxAxisSystem sceneAxisSystem = m_pScene->GetGlobalSettings().GetAxisSystem();
	fbxsdk::FbxAxisSystem::MayaYUp.ConvertScene(m_pScene);

	// �� ������ �ﰢ��ȭ �� �� �ִ� ��� ��带 �ﰢ��ȭ ��Ų��. 
	m_pGeometryConverter->Triangulate(m_pScene, true, true);

}

void FBXParser::LoadNode(fbxsdk::FbxNode* _node, FbxNodeAttribute::EType _attribute)
{
	FbxNodeAttribute* pNodeAtrribute = _node->GetNodeAttribute();

	if (pNodeAtrribute != nullptr)
	{
		FbxString nodename = _node->GetName();
		FbxNodeAttribute::EType attributeType = pNodeAtrribute->GetAttributeType();
		if (attributeType == _attribute)
		{
			switch (pNodeAtrribute->GetAttributeType())
			{
			case FbxNodeAttribute::eSkeleton:
				ProcessSkeleton(_node);
				break;
			case FbxNodeAttribute::eMesh:
				ProcessMesh(_node);
				break;
			default:
				break;
			}
		}
	}

	const unsigned int childCount = _node->GetChildCount();
	for (unsigned int i = 0; i < childCount; i++)
	{
		// �ڽ� ��尡 �ε��̵Ǿ��ִٴ� ����� �� �� �ִ�
		std::string childName = _node->GetName();
		LoadNode(_node->GetChild(i), _attribute);
	}
}

void FBXParser::ProcessMesh(fbxsdk::FbxNode* _node)
{
	// ���ο� �Ž�(m_pMesh) ����
	m_pMesh = std::make_shared<ParsingData::Mesh>();
	m_pFBXModel->pMesh_V.push_back(m_pMesh);

	// ���° �ε������� 
	m_pMesh->meshIndex = m_pFBXModel->pMesh_V.size() - 1;
	m_pFBXmesh = _node->GetMesh();

	// ��Ʈ������ �׻� ù��° ���� �����´� + ������ Mesh�� ��Ʈ���� �̸��� �˷��ش�
	fbxsdk::FbxSurfaceMaterial* material = _node->GetMaterial(0);
	if (material != nullptr)
	{
		m_pFBXModel->materialName_V.push_back(material->GetName());
		m_pMesh->materialName = material->GetName();
	}

	m_pMesh->nodeName = _node->GetName();

	//�θ�, �ڽ� ��� ���� ����
	if (_node->GetParent() != nullptr)
	{
		m_pMesh->isParentExist = true;
		m_pMesh->nodeParentName = _node->GetParent()->GetName();

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

	// Node TRS ����, Mesh�� �ֱ� ������ �ι�° ���ڴ� null�� �Ѱ��ش�
	SetTransform(_node, nullptr);

	std::vector<BoneWeights> boneWeight_V;
	if (m_HasSkeleton == true)
	{
		// Vertex ������ŭ BoneWeight ����..
		// �ش� Vertex Index�� ������ Index�� ����ġ ��, Bone Index Data ����..
		boneWeight_V.resize(m_pFBXmesh->GetControlPointsCount());

		bool isSkin = false;
		// Boxó�� Bone�� ���� ������ ��������
		isSkin = ProcessBoneWeights(_node, boneWeight_V);
		m_pMesh->isSkinningObject = true;
	}

	//CreateVertex(m_pFBXmesh, boneWeights, m_pFBXmesh->GetControlPointsCount());

	// Bone Data ���� ����� ���� Skinning Object �Ǻ�..
	/// �ε��� ���� ����
	//m_pMesh->meshNumIndex = ProcessMeshVertexIndex();

	/// uv, �븻, ���̳븻, ź��Ʈ�� �߰�
	//ProcessMeshVertexInfo();

	if (m_pSkeleton != nullptr)
	{
		m_pSkeleton->m_BoneOffsets = m_BoneOffsets;
	}

	/// ���ؽ� ���ø�
	//SplitMesh2();

	for (int i = 0; i < m_pMesh->meshFace_V.size(); i++)
	{
		//MakeTangentSpace(m_pFBXmesh, i);
	}

	for (int i = 0; i < m_pMesh->meshFace_V.size(); i++)
	{
		//MakeBinormal(i);
	}

	/// ���ؽ� ���ø��� �ε��� ���� ����
	//?? �ε����� �����ϰ� �ִϱ� ���൵ �ǳ�??
	unsigned int optVertexCount = 0;

	// ���ؽ� ���ø� �� �ε��� ����
	m_pMesh->pOptIndex = new ParsingData::IndexList[m_pMesh->meshFace_V.size() * 3];

	for (unsigned int i = 0; i < m_pMesh->meshFace_V.size(); i++)
	{
		ParsingData::Face* nowFace = m_pMesh->meshFace_V[i];

		for (unsigned int j = 0; j < 3; j++)
		{
			switch (j)
			{
			case 0:
				m_pMesh->pOptIndex[i].index_A[j] = nowFace->vertexIndex_A[0];
				break;
			case 1:
				m_pMesh->pOptIndex[i].index_A[j] = nowFace->vertexIndex_A[2];
				break;
			case 2:
				m_pMesh->pOptIndex[i].index_A[j] = nowFace->vertexIndex_A[1];
				break;
			default:
				break;
			}
		}
		//�ε��� ������ ����
		optVertexCount++;
	}

	m_pMesh->optIndexNum = optVertexCount;
	//+ �� ���ؽ����� ��������Ѵ�  
}

void FBXParser::ProcessSkeleton(fbxsdk::FbxNode* _node)
{
	FbxSkeleton* fbxSkeleton = _node->GetSkeleton();
	if (fbxSkeleton == nullptr) return;

	// ���ο� �޽������� ���� Ȯ��
	if (m_pSkeleton == nullptr)
	{
		m_pSkeleton = std::make_unique<ParsingData::Skeleton>();

		// ���̷����� �ִٸ� ��Ű�� �ִϸ��̼�
		m_pFBXModel->isSkinnedAnimation = true;
		m_HasSkeleton = true;
	}

	ParsingData::Bone* nowBone = new ParsingData::Bone();

	// �θ� Bone Index�� -1 �̸� �ֻ��� Root Node..
	// �ֻ��� ���(�θ���)���� Ȯ��..
	int parentBoneIndex = -1;
	FbxNode* pParentNode = _node->GetParent();

	if (pParentNode != nullptr)
	{
		std::string nodeName = pParentNode->GetName();
		parentBoneIndex = m_pSkeleton->FindBoneIndex(nodeName);

		nowBone->parentBoneName = _node->GetParent()->GetName();
		nowBone->isParentExist = true;

		if (0 <= parentBoneIndex)
		{
			nowBone->pParentBone = m_pSkeleton->m_Bones[parentBoneIndex];
		}

		if (nowBone->pParentBone != nullptr)
		{
			nowBone->pParentBone->childBoneList_V.push_back(nowBone);
		}
	}
	else
	{
		nowBone->isParentExist = false;
	}

	nowBone->boneName = _node->GetName();
	nowBone->parentBoneIndex = parentBoneIndex;
	m_pSkeleton->AddBone(nowBone);

	// Node TRS ����
	SetTransform(_node, nowBone);

	// ���� ������ return
	if (_node->GetSkeleton() == nullptr)
	{
		return;
	}

	nowBone->boneIndex = static_cast<int>(m_pSkeleton->m_Bones.size() - 1);	// 0������ �����ϰ� �Ϸ���
	nowBone->isBoneSet = true;
	nowBone->minmum = DirectX::SimpleMath::Vector3(+FLT_MAX, +FLT_MAX, +FLT_MAX);
	nowBone->maximum = DirectX::SimpleMath::Vector3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
}

void FBXParser::SetTransform(fbxsdk::FbxNode* _node, ParsingData::Bone* _bone)
{
	if (_node == nullptr) return;

	FbxMatrix _worldpos = m_pScene->GetAnimationEvaluator()->GetNodeGlobalTransform(_node);
	FbxMatrix _localpos = m_pScene->GetAnimationEvaluator()->GetNodeLocalTransform(_node);
	FbxMatrix _newMat = multT(_node);
	FbxMatrix _newMatGeom = multTGeom(_node);

	// �޾ƿ� ����� ����TM�� �������ش�(yz�� ���� �����̶�� ����)
	DirectX::SimpleMath::Matrix _world = ConvertMatrix(_worldpos);
	DirectX::SimpleMath::Matrix _local = ConvertMatrix(_localpos);
	DirectX::SimpleMath::Matrix _newMat2 = ConvertMatrix(_newMat);
	DirectX::SimpleMath::Matrix _newMatGeom2 = ConvertMatrix(_newMatGeom);

	switch (_node->GetNodeAttribute()->GetAttributeType())
	{
	case FbxNodeAttribute::eSkeleton:
	{
		// ��Ʈ ���� ó�����ش�?
		if (_bone->pParentBone == nullptr)
		{
			const auto yaw = -90.0f * DirectX::XM_PI / 180.0f;

			DirectX::SimpleMath::Quaternion q = DirectX::XMQuaternionRotationRollPitchYaw(yaw, 0.0f, 0.0f);

			_world *= XMMatrixRotationQuaternion(q);
			_local *= XMMatrixRotationQuaternion(q);
		}
		break;
	}

	//// �޾ƿ� ����� ����TM�� �������ش�(yz�� ���� �����̶�� ����)
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

	//��尡 ����� �Ž��Ŀ� ���� �־��ִ°� �ٸ�
	switch (_node->GetNodeAttribute()->GetAttributeType())
	{
		case FbxNodeAttribute::eSkeleton:
		{
			_bone->tmRow0 = DirectX::SimpleMath::Vector3(r1);
			_bone->tmRow1 = DirectX::SimpleMath::Vector3(r2);
			_bone->tmRow2 = DirectX::SimpleMath::Vector3(r3);
			_bone->tmRow3 = DirectX::SimpleMath::Vector3(r4);

			_bone->worldTM = _world;
			_bone->localTM = _local;
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

bool FBXParser::ProcessBoneWeights(fbxsdk::FbxNode* _node, std::vector<BoneWeights>& _meshBoneWeights)
{
	int deformerCount = m_pFBXmesh->GetDeformerCount();

	// DeformerCount�� 1���� ������ Bone Data�� ���ٰ� ����..
	if (deformerCount < 1) return false;

	// ���̷���-���� size��ŭ BoneAnimation�� Resize�Ѵ�.

	for (int i = 0; i < deformerCount; ++i)
	{
		// Deform : �����Ǵ�
		FbxDeformer* deformer = m_pFBXmesh->GetDeformer(i);

		if (deformer == nullptr) continue;

		if (deformer->GetDeformerType() == FbxDeformer::eSkin)
		{
			FbxSkin* skin = reinterpret_cast<FbxSkin*>(m_pFBXmesh->GetDeformer(i, FbxDeformer::eSkin));

			if (skin == nullptr) continue;

			// Cluster�� ����ġ�� ���� �޽����� �κ������̴�
			// ��Ų �ȿ� �ִ� ��� Ŭ����Ʈ���� ����
			int clusterCount = skin->GetClusterCount();

			FbxCluster::ELinkMode linkMode;

			// Skin Mesh üũ..
			//JMParserData::Mesh* skinMesh = FindMesh(node->GetName());
			std::vector<BoneWeights> skinBoneWeights(_meshBoneWeights.size());
			for (int clusterIndex = 0; clusterIndex < clusterCount; clusterIndex++)
			{
				FbxCluster* cluster = skin->GetCluster(clusterIndex);
				if (cluster == nullptr) continue;
				linkMode = cluster->GetLinkMode();

				FbxNode* pLinkNode = cluster->GetLink();
				if (pLinkNode == nullptr) continue;
				std::string _currJointName = pLinkNode->GetName();

				// ���� joint(��)�� �̸��� ���� index�� ���ؿ´�
				int boneIndex = m_pSkeleton->FindBoneIndex(_currJointName);
				if (boneIndex < 0)
				{
					continue;
				}

				// Bone Index�� �ش��ϴ� Bone ����..
				ParsingData::Bone* _nowBone = m_pSkeleton->m_Bones[boneIndex];

				FbxAMatrix matClusterTransformMatrix;
				FbxAMatrix matClusterLinkTransformMatrix;

				cluster->GetTransformMatrix(matClusterTransformMatrix);
				cluster->GetTransformLinkMatrix(matClusterLinkTransformMatrix);

				// Bone Matrix ����..
				DirectX::SimpleMath::Matrix clusterMatrix = ConvertMatrix(matClusterTransformMatrix);
				DirectX::SimpleMath::Matrix clusterlinkMatrix = ConvertMatrix(matClusterLinkTransformMatrix);

				_nowBone->bindPoseTransform = clusterlinkMatrix;
				_nowBone->boneReferenceTransform = clusterMatrix;

				// BindPose ����� ���ϴ� ����
				const FbxVector4 lT = _node->GetGeometricTranslation(FbxNode::eDestinationPivot);
				const FbxVector4 lR = _node->GetGeometricRotation(FbxNode::eDestinationPivot);
				const FbxVector4 lS = _node->GetGeometricScaling(FbxNode::eDestinationPivot);

				FbxAMatrix geometryTransform = FbxAMatrix(lT, lR, lS);
				DirectX::SimpleMath::Matrix geometryMatrix = ConvertMatrix(geometryTransform);

				// OffsetMatrix�� WorldBindPose�� �����
				DirectX::SimpleMath::Matrix offsetMatrix = clusterMatrix * clusterlinkMatrix.Invert() * geometryMatrix;

				m_BoneOffsets[boneIndex] = offsetMatrix;


				// Bone Mesh üũ..
				// ��Ʈ������ ���� index�� �����ֱ� ���� �۾��ε�

				for (int j = 0; j < cluster->GetControlPointIndicesCount(); ++j)
				{
					int index = cluster->GetControlPointIndices()[j];
					double weight = cluster->GetControlPointWeights()[j];

					skinBoneWeights[index].AddBoneWeight(boneIndex, (float)weight);
				}
			}

			switch (linkMode)
			{
			case FbxCluster::eNormalize:
			{
				// ����ġ ���� 1.0���� ����� �۾�..
				for (int i = 0; i < (int)skinBoneWeights.size(); ++i)
					skinBoneWeights[i].Normalize();
			}
			break;

			case FbxCluster::eAdditive:
				// ����ġ�� ���̵� �׳� �ջ�
				break;

			case FbxCluster::eTotalOne:
				// �̹� ����ȭ�� �Ǿ��ִ� ���
				break;
			}

			for (size_t i = 0; i < _meshBoneWeights.size(); i++)
				_meshBoneWeights[i].AddBoneWeights(skinBoneWeights[i]);
		}
	}

	return true;
}

void FBXParser::LoadMaterial(std::vector<MaterialDesc>& _outMaterials)
{
	unsigned int nowMatCount = m_pScene->GetMaterialCount();

	for (unsigned int i = 0; i < nowMatCount; i++)
	{
		MaterialDesc materialDesc;

		fbxsdk::FbxSurfaceMaterial* nowMater = m_pScene->GetMaterial(i);

		// �ؽ��� �̸��� �����ö� �ڿ� Ȯ���ڰ� �Ⱥٴ´�.
		GetMaterialTexture(nowMater, materialDesc);

		if (nowMater->GetClassId().Is(fbxsdk::FbxSurfacePhong::ClassId))
		{
			materialDesc.diffuse = ConvertVector3(reinterpret_cast<fbxsdk::FbxSurfacePhong*>(nowMater)->Diffuse);
			materialDesc.ambient = ConvertVector3(reinterpret_cast<fbxsdk::FbxSurfacePhong*>(nowMater)->Ambient);
			materialDesc.emissive = ConvertVector3(reinterpret_cast<fbxsdk::FbxSurfacePhong*>(nowMater)->Emissive);
			materialDesc.fresnelR0 = ConvertVector3(reinterpret_cast<fbxsdk::FbxSurfacePhong*>(nowMater)->Reflection);
			materialDesc.specular = ConvertVector3(reinterpret_cast<fbxsdk::FbxSurfacePhong*>(nowMater)->Specular);
			
			materialDesc.transparentFactor = ConvertFloat(reinterpret_cast<fbxsdk::FbxSurfacePhong*>(nowMater)->TransparencyFactor);
			materialDesc.specularPower = ConvertFloat(reinterpret_cast<fbxsdk::FbxSurfacePhong*>(nowMater)->SpecularFactor);
			materialDesc.shineness = ConvertFloat(reinterpret_cast<fbxsdk::FbxSurfacePhong*>(nowMater)->Shininess);
			materialDesc.reflactionFactor = ConvertFloat(reinterpret_cast<fbxsdk::FbxSurfacePhong*>(nowMater)->ReflectionFactor);
		}
		else if (nowMater->GetClassId().Is(fbxsdk::FbxSurfaceLambert::ClassId))
		{
			materialDesc.diffuse = ConvertVector3(reinterpret_cast<fbxsdk::FbxSurfaceLambert*>(nowMater)->Diffuse);
			materialDesc.ambient = ConvertVector3(reinterpret_cast<fbxsdk::FbxSurfaceLambert*>(nowMater)->Ambient);
			materialDesc.emissive = ConvertVector3(reinterpret_cast<fbxsdk::FbxSurfaceLambert*>(nowMater)->Emissive);
		}

		_outMaterials.push_back(materialDesc);
	}
}

void FBXParser::GetMaterialTexture(fbxsdk::FbxSurfaceMaterial* _fbxSurMaterial, MaterialDesc& _outDesc)
{
	unsigned int textureIndex = 0;
	FbxProperty prop;
	
	FBXSDK_FOR_EACH_TEXTURE(textureIndex)
	{
		prop = _fbxSurMaterial->FindProperty(fbxsdk::FbxLayerElement::sTextureChannelNames[textureIndex]);
	
		_outDesc.materialName = _fbxSurMaterial->GetName();
	
		if (prop.IsValid())
		{
			prop = _fbxSurMaterial->FindProperty(fbxsdk::FbxSurfaceMaterial::sEmissive);
			LoadTextureProperty(prop, _outDesc);
	
			prop = _fbxSurMaterial->FindProperty(fbxsdk::FbxSurfaceMaterial::sDiffuse);
			LoadTextureProperty(prop, _outDesc);
	
			prop = _fbxSurMaterial->FindProperty(fbxsdk::FbxSurfaceMaterial::sSpecular);
			LoadTextureProperty(prop, _outDesc);
	
			prop = _fbxSurMaterial->FindProperty(fbxsdk::FbxSurfaceMaterial::sShininess);
			LoadTextureProperty(prop, _outDesc);
	
			prop = _fbxSurMaterial->FindProperty(fbxsdk::FbxSurfaceMaterial::sBump);
			LoadTextureProperty(prop, _outDesc);
	
			prop = _fbxSurMaterial->FindProperty(fbxsdk::FbxSurfaceMaterial::sNormalMap);
			LoadTextureProperty(prop, _outDesc);
	
			prop = _fbxSurMaterial->FindProperty(fbxsdk::FbxSurfaceMaterial::sTransparentColor);
			LoadTextureProperty(prop, _outDesc);
	
			prop = _fbxSurMaterial->FindProperty(fbxsdk::FbxSurfaceMaterial::sReflection);
			LoadTextureProperty(prop, _outDesc);
	
			prop = _fbxSurMaterial->FindProperty(fbxsdk::FbxSurfaceMaterial::sDisplacementColor);
			LoadTextureProperty(prop, _outDesc);
		}
	}
}

void FBXParser::LoadTextureProperty(fbxsdk::FbxProperty& _prop, MaterialDesc& _outDesc)
{
	std::string propertyName = _prop.GetName().Buffer();

	int numberOfLayeredTextures = _prop.GetSrcObjectCount<FbxLayeredTexture>();

	if (0 != numberOfLayeredTextures)
	{
		return;
	}
	else
	{
		int numberOfTextures = _prop.GetSrcObjectCount<FbxTexture>();

		//FbxTexture* texture = fbxsdk::FbxCast<FbxTexture>(_prop.GetSrcObject<FbxTexture>(0));
		//
		//FbxFileTexture* fileTexture = fbxsdk::FbxCast<FbxFileTexture>(texture);
		//
		//LoadTextureToMaterial(propertyName, fileTexture, _outDesc);

		if (1 < numberOfTextures)
		{
			for (int i = 0; i < numberOfTextures; i++)
			{
				FbxTexture* texture = fbxsdk::FbxCast<FbxTexture>(_prop.GetSrcObject<FbxTexture>(i));
		
				FbxFileTexture* fileTexture = fbxsdk::FbxCast<FbxFileTexture>(texture);
		
				LoadTextureToMaterial(propertyName, fileTexture, _outDesc);
			}
		}
		
		if (1 == numberOfTextures)
		{
			FbxTexture* texture = fbxsdk::FbxCast<FbxTexture>(_prop.GetSrcObject<FbxTexture>(0));
		
			FbxFileTexture* fileTexture = fbxsdk::FbxCast<FbxFileTexture>(texture);
		
			LoadTextureToMaterial(propertyName, fileTexture, _outDesc);
		}
	}
}

void FBXParser::LoadTextureToMaterial(std::string _propertyName, fbxsdk::FbxFileTexture* _fileTexture, MaterialDesc& _outDesc)
{
	if (_fileTexture != nullptr)
	{
		std::string nowTextureName = _fileTexture->GetFileName();

		if (_propertyName == "EmissiveColor")
		{
			_outDesc.textureName_V[EMISSIVE_TEXUTRE] = StringHelper::GetFileName(nowTextureName, true);
		}
		else if (_propertyName == "DiffuseColor")
		{
			_outDesc.textureName_V[DIFFUSE_TEXUTRE] = StringHelper::GetFileName(nowTextureName, true);
		}
		else if (_propertyName == "SpecularColor")
		{
			_outDesc.textureName_V[SPECULAR_TEXUTRE] = StringHelper::GetFileName(nowTextureName, true);
		}
		else if (_propertyName == "ShininessExponent")
		{
			_outDesc.textureName_V[SHININESS_TEXUTRE] = StringHelper::GetFileName(nowTextureName, true);
		}
		else if (_propertyName == "Bump" || _propertyName == "NormalMap")
		{
			_outDesc.textureName_V[BUMP_TEXUTRE] = StringHelper::GetFileName(nowTextureName, true);
		}
		else if (_propertyName == "TransparentColor")
		{
			_outDesc.textureName_V[TRANSPARENT_TEXUTRE] = StringHelper::GetFileName(nowTextureName, true);
		}
		else if (_propertyName == "ReflectionColor")
		{
			_outDesc.textureName_V[REFLECTION_TEXUTRE] = StringHelper::GetFileName(nowTextureName, true);
		}
		else if (_propertyName == "DisplacementColor")
		{
			_outDesc.textureName_V[DISPLACEMENT_TEXUTRE] = StringHelper::GetFileName(nowTextureName, true);
		}
	}
}

DirectX::SimpleMath::Matrix FBXParser::ConvertMatrix(const FbxMatrix& _fbxMatrix)
{
	// 2��, 3�� ����..
	FbxVector4 r1 = _fbxMatrix.GetRow(0);
	FbxVector4 r2 = _fbxMatrix.GetRow(1);
	FbxVector4 r3 = _fbxMatrix.GetRow(2);
	FbxVector4 r4 = _fbxMatrix.GetRow(3);

	return DirectX::SimpleMath::Matrix
	(
		ConvertVector4(r1),
		ConvertVector4(r3),
		ConvertVector4(r2),
		ConvertVector4(r4)
	);
}

DirectX::SimpleMath::Vector4 FBXParser::ConvertVector4(const FbxVector4& _fbxVector4)
{
	// xyzw -> xzyw
	return DirectX::SimpleMath::Vector4
	(
		static_cast<float>(_fbxVector4.mData[0]),
		static_cast<float>(_fbxVector4.mData[2]),
		static_cast<float>(_fbxVector4.mData[1]),
		static_cast<float>(_fbxVector4.mData[3])
	);
}

DirectX::SimpleMath::Vector3 FBXParser::ConvertVector3(const FbxDouble3& _fbxDouble3)
{
	DirectX::SimpleMath::Vector3 vector3;

	vector3.x = static_cast<float>(_fbxDouble3.mData[0]);
	vector3.y = static_cast<float>(_fbxDouble3.mData[1]);
	vector3.z = static_cast<float>(_fbxDouble3.mData[2]);

	return vector3;
}

float FBXParser::ConvertFloat(const FbxDouble& _fbxDouble)
{
	float f = static_cast<float>(_fbxDouble);
	return f;
}

FbxAMatrix FBXParser::multT(FbxNode* _pNode)
{
	FbxAMatrix matrixGeo;
	matrixGeo.SetIdentity();
	if (_pNode->GetNodeAttribute())
	{
		const FbxVector4 lT = _pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
		const FbxVector4 lR = _pNode->GetGeometricRotation(FbxNode::eSourcePivot);
		const FbxVector4 lS = _pNode->GetGeometricScaling(FbxNode::eSourcePivot);
		matrixGeo.SetT(lT);
		matrixGeo.SetR(lR);
		matrixGeo.SetS(lS);
	}
	FbxAMatrix localMatrix = _pNode->EvaluateLocalTransform();

	FbxNode* pParentNode = _pNode->GetParent();
	FbxAMatrix parentMatrix = pParentNode->EvaluateLocalTransform();
	while ((pParentNode = pParentNode->GetParent()) != NULL)
	{
		parentMatrix = pParentNode->EvaluateLocalTransform() * parentMatrix;
	}

	FbxAMatrix matrix = parentMatrix * localMatrix * matrixGeo;
	//FbxVector4 result = matrix.MultT(vector);
	return matrix;
}

FbxVector4 FBXParser::multT(FbxNode* _pNode, FbxVector4 _fbxVector4)
{
	FbxAMatrix matrixGeo;
	matrixGeo.SetIdentity();
	if (_pNode->GetNodeAttribute())
	{
		const FbxVector4 lT = _pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
		const FbxVector4 lR = _pNode->GetGeometricRotation(FbxNode::eSourcePivot);
		const FbxVector4 lS = _pNode->GetGeometricScaling(FbxNode::eSourcePivot);
		matrixGeo.SetT(lT);
		matrixGeo.SetR(lR);
		matrixGeo.SetS(lS);
	}
	FbxAMatrix localMatrix = _pNode->EvaluateLocalTransform();

	FbxNode* pParentNode = _pNode->GetParent();
	FbxAMatrix parentMatrix = pParentNode->EvaluateLocalTransform();
	while ((pParentNode = pParentNode->GetParent()) != NULL)
	{
		parentMatrix = pParentNode->EvaluateLocalTransform() * parentMatrix;
	}

	FbxAMatrix matrix = parentMatrix * localMatrix * matrixGeo;
	FbxVector4 result = matrix.MultT(_fbxVector4);
	return result;
}

FbxAMatrix FBXParser::multTGeom(FbxNode* _pNode)
{
	FbxAMatrix matrixGeo;
	matrixGeo.SetIdentity();
	if (_pNode->GetNodeAttribute())
	{
		const FbxVector4 lT = _pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
		const FbxVector4 lR = _pNode->GetGeometricRotation(FbxNode::eSourcePivot);
		const FbxVector4 lS = _pNode->GetGeometricScaling(FbxNode::eSourcePivot);
		matrixGeo.SetT(lT);
		matrixGeo.SetR(lR);
		matrixGeo.SetS(lS);
	}
	FbxAMatrix localMatrix = _pNode->EvaluateLocalTransform();

	FbxNode* pParentNode = _pNode->GetParent();
	FbxAMatrix parentMatrix = pParentNode->EvaluateLocalTransform();
	while ((pParentNode = pParentNode->GetParent()) != NULL)
	{
		parentMatrix = pParentNode->EvaluateLocalTransform() * parentMatrix;
	}

	FbxAMatrix matrix = parentMatrix * localMatrix * matrixGeo;
	//FbxVector4 result = matrix.MultT(vector);
	return matrixGeo;
}
