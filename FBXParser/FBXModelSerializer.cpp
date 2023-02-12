#include "pch.h"
#include "FBXModelSerializer.h"

#include "FBXParser.h"
#include "BinaryFileLayout.h"

FBXModelSerializer::FBXModelSerializer()
	: m_DataFile(nullptr)
{
}

FBXModelSerializer::~FBXModelSerializer()
{
}

///---------------------------------
/// ��ܿ�
///---------------------------------
void FBXModelSerializer::SaveBinaryFileFBX(FBXModel* _originModel, std::vector<MaterialDesc>& _materialDesc, const char* _filePath)
{
	m_DataFile = std::make_unique<FBXModelBinaryFile>();

	// ���� �������� �����ؼ� ���ο��ü�� ��Ƴ��´�.
	OrganizeFBXModelFile(_originModel, _materialDesc);
	// bin���Ϸ� ��������.
	WriteBinarayFile(_filePath);
	// txt���Ϸ� ��������.
	WriteTextFile(_filePath);
}

///---------------------------------
/// �Ҵܿ�
///---------------------------------
void FBXModelSerializer::OrganizeFBXModelFile(FBXModel* _originModel, std::vector<MaterialDesc>& _materialDesc)
{
	// ��� ����ü�� ���� �������� ����(������ �ִ��� ����, ������ ���� ��...)�� ����
	OrganizeFBXModelHeader(_originModel, _materialDesc);
	// ������ ����ü�� ���� �������� ����
	OrganizeFBXModelData(_originModel, _materialDesc);
}

void FBXModelSerializer::WriteBinarayFile(const char* _filePath)
{
	std::string fullName(_filePath);
	fullName.append(".bin");

	std::ofstream binaryFile(fullName.c_str(), std::ios::out | std::ios::binary);

	if (binaryFile.is_open())
	{
		/// ���
		WriteBinarayHeaderFile(&binaryFile);

		/// ������
		WriteBinarayDataFile(&binaryFile);
	}

	binaryFile.close();
}

void FBXModelSerializer::WriteTextFile(const char* _filePath)
{
}
///---------------------------------
///Organize
///---------------------------------
/// ���
void FBXModelSerializer::OrganizeFBXModelHeader(FBXModel* _originModel, std::vector<MaterialDesc>& _materialDesc)
{
	// �Ž�
	OrganizeHeaderMesh(_originModel);

	// ���׸���
	OrganizeHeaderMaterial(_originModel, _materialDesc);
	
	// ���̷���
	//OrganizeHeaderSkeleton(_originModel);
	
	// �ִϸ��̼�
	//OrganizeHeaderAnimation(_originModel);
}

void FBXModelSerializer::OrganizeHeaderMesh(FBXModel* _originModel)
{
	m_DataFile->binHeader.meshCount = static_cast<int>(_originModel->pMesh_V.size());
	m_DataFile->binHeader.vertexCount_V.resize(_originModel->pMesh_V.size());
	m_DataFile->binHeader.indexCount_V.resize(_originModel->pMesh_V.size());

	for (int i = 0; i < _originModel->pMesh_V.size(); ++i)
	{
		m_DataFile->binHeader.vertexCount_V[i] = static_cast<int>(_originModel->pMesh_V[i]->optVertex_V.size());
		m_DataFile->binHeader.indexCount_V[i] = static_cast<int>(_originModel->pMesh_V[i]->optIndexNum * 3);
	}
}

void FBXModelSerializer::OrganizeHeaderMaterial(FBXModel* _originModel, std::vector<MaterialDesc>& _materialDesc)
{
	// ���׸����� �ִ��� ���ٸ� ���͸����� �����ϴ� ������ �ǳ� �ڴ�.
	if (_materialDesc.size() > 0)
	{
		m_DataFile->binHeader.isMaterial = true;
	}
	else
	{
		return;
	}

	// ���׸����� ����	
	m_DataFile->binHeader.materialCount = _materialDesc.size();
	// ���׸��� �̸��� ����
	m_DataFile->binHeader.materialNameLength_V.resize(m_DataFile->binHeader.materialCount);
	for (int i = 0; i < m_DataFile->binHeader.materialCount; ++i)
	{
		m_DataFile->binHeader.materialNameLength_V[i] = static_cast<int>(_materialDesc[i].materialName.length()) + 1;
	}
	// ���׸��� ���ӵǾ��ִ� �ؽ��ĵ��� ����
	m_DataFile->binHeader.textureNameCount_V.resize(m_DataFile->binHeader.materialCount);
	for (int i = 0; i < m_DataFile->binHeader.materialCount; ++i)
	{
		m_DataFile->binHeader.textureNameCount_V[i] = static_cast<int>(_materialDesc[i].textureName_V.size());
	}
	// ���׸��� ���ӵǾ��ִ� �ؽ��ĵ��� �̸��� ����
	m_DataFile->binHeader.textureNameLength_V.resize(m_DataFile->binHeader.materialCount);
	for (int i = 0; i < m_DataFile->binHeader.materialCount; ++i)
	{
		m_DataFile->binHeader.textureNameLength_V[i].resize(_materialDesc[i].textureName_V.size());
		for (int j = 0; j < _materialDesc[i].textureName_V.size(); ++j)
		{
			m_DataFile->binHeader.textureNameLength_V[i][j] = static_cast<int>(_materialDesc[i].textureName_V[j].length()) + 1;
		}
	}
	// ���׸����� �ε���
	m_DataFile->binHeader.materialMapping_V.resize(m_DataFile->binHeader.meshCount);
	for (int i = 0; i < m_DataFile->binHeader.meshCount; i++)
	{
		for (int j = 0; j < _materialDesc.size(); j++)
		{
			if (_originModel->pMesh_V[i]->materialName.compare(_materialDesc[j].materialName) == 0)
			{
				m_DataFile->binHeader.materialMapping_V[i] = j;
				break;
			}
		}
	}
}

void FBXModelSerializer::OrganizeHeaderSkeleton(FBXModel* _originModel)
{
}

void FBXModelSerializer::OrganizeHeaderAnimation(FBXModel* _originModel)
{
}

/// ������
void FBXModelSerializer::OrganizeFBXModelData(FBXModel* _originModel, std::vector<MaterialDesc>& _materialDesc)
{
	// �Ž�
	OrganizeDataMesh(_originModel);
	
	// ���׸���
	OrganizeDataMaterial(_materialDesc);

	// ���̷���
	//OrganizeDataSkeleton(_originModel);

	// �ִϸ��̼�
	//OrganizeDataAnimation(_originModel);
}

void FBXModelSerializer::OrganizeDataMesh(FBXModel* _originModel)
{
	m_DataFile->binData.mesh_V.resize(_originModel->pMesh_V.size());

	for (int i = 0; i < _originModel->pMesh_V.size(); ++i)
	{
		// �Ž��� �������ִ� ���ؽ�����ŭ ũ�⸦ �����ش�.
		m_DataFile->binData.mesh_V[i].vertex_V.resize(_originModel->pMesh_V[i]->optVertex_V.size());

		for (int j = 0; j < _originModel->pMesh_V[i]->optVertex_V.size(); j++)
		{
			// � ���ؽ����� �����Ҽ��ִ� ��絥���� ������ �������ִ� ���ؽ��� ������ ��´�
			m_DataFile->binData.mesh_V[i].vertex_V[j].pos.x = _originModel->pMesh_V[i]->optVertex_V[j]->pos.x;
			m_DataFile->binData.mesh_V[i].vertex_V[j].pos.y = _originModel->pMesh_V[i]->optVertex_V[j]->pos.y;
			m_DataFile->binData.mesh_V[i].vertex_V[j].pos.z = _originModel->pMesh_V[i]->optVertex_V[j]->pos.z;

			m_DataFile->binData.mesh_V[i].vertex_V[j].texCoord.x = _originModel->pMesh_V[i]->optVertex_V[j]->u;
			m_DataFile->binData.mesh_V[i].vertex_V[j].texCoord.y = _originModel->pMesh_V[i]->optVertex_V[j]->v;

			m_DataFile->binData.mesh_V[i].vertex_V[j].normal.x = _originModel->pMesh_V[i]->optVertex_V[j]->normal.x;
			m_DataFile->binData.mesh_V[i].vertex_V[j].normal.y = _originModel->pMesh_V[i]->optVertex_V[j]->normal.y;
			m_DataFile->binData.mesh_V[i].vertex_V[j].normal.z = _originModel->pMesh_V[i]->optVertex_V[j]->normal.z;

			m_DataFile->binData.mesh_V[i].vertex_V[j].tangent.x = _originModel->pMesh_V[i]->optVertex_V[j]->tangent.x;
			m_DataFile->binData.mesh_V[i].vertex_V[j].tangent.y = _originModel->pMesh_V[i]->optVertex_V[j]->tangent.y;
			m_DataFile->binData.mesh_V[i].vertex_V[j].tangent.z = _originModel->pMesh_V[i]->optVertex_V[j]->tangent.z;
			m_DataFile->binData.mesh_V[i].vertex_V[j].tangent.w = _originModel->pMesh_V[i]->optVertex_V[j]->tangent.w;

			m_DataFile->binData.mesh_V[i].vertex_V[j].weights.x = _originModel->pMesh_V[i]->optVertex_V[j]->boneWeight_Arr[0];
			m_DataFile->binData.mesh_V[i].vertex_V[j].weights.y = _originModel->pMesh_V[i]->optVertex_V[j]->boneWeight_Arr[1];
			m_DataFile->binData.mesh_V[i].vertex_V[j].weights.z = _originModel->pMesh_V[i]->optVertex_V[j]->boneWeight_Arr[2];

			m_DataFile->binData.mesh_V[i].vertex_V[j].boneIndices[0] = _originModel->pMesh_V[i]->optVertex_V[j]->boneIndex_Arr[0];
			m_DataFile->binData.mesh_V[i].vertex_V[j].boneIndices[1] = _originModel->pMesh_V[i]->optVertex_V[j]->boneIndex_Arr[1];
			m_DataFile->binData.mesh_V[i].vertex_V[j].boneIndices[2] = _originModel->pMesh_V[i]->optVertex_V[j]->boneIndex_Arr[2];
			m_DataFile->binData.mesh_V[i].vertex_V[j].boneIndices[3] = _originModel->pMesh_V[i]->optVertex_V[j]->boneIndex_Arr[3];

			m_DataFile->binData.mesh_V[i].vertex_V[j].rgba.x = 0.f;
			m_DataFile->binData.mesh_V[i].vertex_V[j].rgba.y = 0.f;
			m_DataFile->binData.mesh_V[i].vertex_V[j].rgba.z = 0.f;
			m_DataFile->binData.mesh_V[i].vertex_V[j].rgba.w = 0.f;
		}

		m_DataFile->binData.mesh_V[i].index_V.resize(static_cast<size_t>(_originModel->pMesh_V[i]->optIndexNum * 3));

		// ParsingData���� �ε��� ���� �����´�
		for (int j = 0; j < _originModel->pMesh_V[i]->optIndexNum; j++)
		{
			m_DataFile->binData.mesh_V[i].index_V[j * 3 + 0] = static_cast<DWORD>(_originModel->pMesh_V[i]->pOptIndex[j].index_A[0]);
			m_DataFile->binData.mesh_V[i].index_V[j * 3 + 1] = static_cast<DWORD>(_originModel->pMesh_V[i]->pOptIndex[j].index_A[1]);
			m_DataFile->binData.mesh_V[i].index_V[j * 3 + 2] = static_cast<DWORD>(_originModel->pMesh_V[i]->pOptIndex[j].index_A[2]);
		}

		m_DataFile->binData.mesh_V[i].meshIndex = _originModel->pMesh_V[i]->meshIndex;
		m_DataFile->binData.mesh_V[i].isParent = _originModel->pMesh_V[i]->isParentExist;
		if (m_DataFile->binData.mesh_V[i].isParent == true)
		{
			m_DataFile->binData.mesh_V[i].parentIndex = _originModel->pMesh_V[i]->pNodeParentMesh->meshIndex;
		}

		Float4x4Func _temp;

		_temp = _originModel->pMesh_V[i]->worldTM;
		m_DataFile->binData.mesh_V[i].meshWorldTM = _temp;

		_temp = _originModel->pMesh_V[i]->localTM;
		m_DataFile->binData.mesh_V[i].meshLocalTM = _temp;
	}
}

void FBXModelSerializer::OrganizeDataMaterial(std::vector<MaterialDesc>& _materialDesc)
{
	if (m_DataFile->binHeader.isMaterial == true)
	{
		m_DataFile->binData.material_V = _materialDesc;
	}
}

void FBXModelSerializer::OrganizeDataSkeleton(FBXModel* _originModel)
{
}

void FBXModelSerializer::OrganizeDataAnimation(FBXModel* _originModel)
{
}

///---------------------------------
/// Write
///---------------------------------
/// ���
void FBXModelSerializer::WriteBinarayHeaderFile(std::ofstream* _out)
{
	//-------------------------------------
	// �Ž�
	//-------------------------------------
	_out->write(reinterpret_cast<char*>(&(m_DataFile->binHeader.meshCount)), sizeof(m_DataFile->binHeader.meshCount));
	_out->write(reinterpret_cast<char*>(m_DataFile->binHeader.vertexCount_V.data()), sizeof(int) * m_DataFile->binHeader.vertexCount_V.size());
	_out->write(reinterpret_cast<char*>(m_DataFile->binHeader.indexCount_V.data()), sizeof(int) * m_DataFile->binHeader.indexCount_V.size());
	_out->write(reinterpret_cast<char*>(&m_DataFile->binHeader.vertexType), sizeof(m_DataFile->binHeader.vertexType));

	//-------------------------------------
	// ���׸���
	//-------------------------------------
	_out->write(reinterpret_cast<char*>(&m_DataFile->binHeader.isMaterial), sizeof(m_DataFile->binHeader.isMaterial));
	if (m_DataFile->binHeader.isMaterial == true)
	{
		_out->write(reinterpret_cast<char*>(&(m_DataFile->binHeader.materialCount)), sizeof(m_DataFile->binHeader.materialCount));
		_out->write(reinterpret_cast<char*>(m_DataFile->binHeader.materialNameLength_V.data()), sizeof(int) * m_DataFile->binHeader.materialNameLength_V.size());
		_out->write(reinterpret_cast<char*>(m_DataFile->binHeader.textureNameCount_V.data()), sizeof(int) * m_DataFile->binHeader.textureNameCount_V.size());
		for (int i = 0; i < m_DataFile->binHeader.textureNameLength_V.size(); ++i)
		{
			_out->write(reinterpret_cast<char*>(m_DataFile->binHeader.textureNameLength_V[i].data()), ((sizeof(int) * m_DataFile->binHeader.textureNameLength_V[i].size())));
		}
		_out->write(reinterpret_cast<char*>(m_DataFile->binHeader.materialMapping_V.data()), sizeof(int) * m_DataFile->binHeader.materialMapping_V.size());
	}
}

/// ������
void FBXModelSerializer::WriteBinarayDataFile(std::ofstream* _out)
{
	//-------------------------------------
	// �Ž�
	//-------------------------------------
	for (int i = 0; i < m_DataFile->binData.mesh_V.size(); ++i)
	{
		_out->write(reinterpret_cast<char*>(m_DataFile->binData.mesh_V[i].vertex_V.data()), sizeof(Vertex::SerializerVertex) * m_DataFile->binData.mesh_V[i].vertex_V.size());
		_out->write(reinterpret_cast<char*>(m_DataFile->binData.mesh_V[i].index_V.data()), sizeof(DWORD) * m_DataFile->binData.mesh_V[i].index_V.size());

		_out->write(reinterpret_cast<char*>(&m_DataFile->binData.mesh_V[i].meshIndex), sizeof(int));
		_out->write(reinterpret_cast<char*>(&m_DataFile->binData.mesh_V[i].isParent), sizeof(bool));
		_out->write(reinterpret_cast<char*>(&m_DataFile->binData.mesh_V[i].parentIndex), sizeof(int));

		_out->write(reinterpret_cast<char*>(&m_DataFile->binData.mesh_V[i].meshWorldTM), sizeof(Float4x4));
		_out->write(reinterpret_cast<char*>(&m_DataFile->binData.mesh_V[i].meshLocalTM), sizeof(Float4x4));
	}

	//-------------------------------------
	// ���׸���
	//-------------------------------------
	if (m_DataFile->binHeader.isMaterial == true)
	{
		for (int i = 0; i < m_DataFile->binData.material_V.size(); ++i)
		{
			_out->write(m_DataFile->binData.material_V[i].materialName.c_str(), static_cast<size_t>(m_DataFile->binHeader.materialNameLength_V[i]) - 1);
			_out->write("\0", 1);

			for (int j = 0; j < m_DataFile->binData.material_V[i].textureName_V.size(); ++j)
				//for (int j = 0; j < m_DataFile->binData.material_V.size(); ++j)
			{
				_out->write(m_DataFile->binData.material_V[i].textureName_V[j].c_str(), static_cast<size_t>(m_DataFile->binHeader.textureNameLength_V[i][j]) - 1);
				_out->write("\0", 1);
			}

			_out->write(reinterpret_cast<char*>(&m_DataFile->binData.material_V[i].diffuse.x), sizeof(float));
			_out->write(reinterpret_cast<char*>(&m_DataFile->binData.material_V[i].diffuse.y), sizeof(float));
			_out->write(reinterpret_cast<char*>(&m_DataFile->binData.material_V[i].diffuse.z), sizeof(float));

			_out->write(reinterpret_cast<char*>(&m_DataFile->binData.material_V[i].emissive.x), sizeof(float));
			_out->write(reinterpret_cast<char*>(&m_DataFile->binData.material_V[i].emissive.y), sizeof(float));
			_out->write(reinterpret_cast<char*>(&m_DataFile->binData.material_V[i].emissive.z), sizeof(float));

			_out->write(reinterpret_cast<char*>(&m_DataFile->binData.material_V[i].ambient.x), sizeof(float));
			_out->write(reinterpret_cast<char*>(&m_DataFile->binData.material_V[i].ambient.y), sizeof(float));
			_out->write(reinterpret_cast<char*>(&m_DataFile->binData.material_V[i].ambient.z), sizeof(float));

			_out->write(reinterpret_cast<char*>(&m_DataFile->binData.material_V[i].fresnelR0.x), sizeof(float));
			_out->write(reinterpret_cast<char*>(&m_DataFile->binData.material_V[i].fresnelR0.y), sizeof(float));
			_out->write(reinterpret_cast<char*>(&m_DataFile->binData.material_V[i].fresnelR0.z), sizeof(float));

			_out->write(reinterpret_cast<char*>(&m_DataFile->binData.material_V[i].specular.x), sizeof(float));
			_out->write(reinterpret_cast<char*>(&m_DataFile->binData.material_V[i].specular.y), sizeof(float));
			_out->write(reinterpret_cast<char*>(&m_DataFile->binData.material_V[i].specular.z), sizeof(float));
	
			_out->write(reinterpret_cast<char*>(&m_DataFile->binData.material_V[i].transparentFactor), sizeof(float));
			_out->write(reinterpret_cast<char*>(&m_DataFile->binData.material_V[i].specularPower), sizeof(float));
			_out->write(reinterpret_cast<char*>(&m_DataFile->binData.material_V[i].shineness), sizeof(float));
			_out->write(reinterpret_cast<char*>(&m_DataFile->binData.material_V[i].reflactionFactor), sizeof(float));
		}
	}
}
