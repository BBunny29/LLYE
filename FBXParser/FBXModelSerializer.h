#pragma once
#include <memory.h>
#include <fstream>

struct FBXModel;
struct MaterialDesc;
struct FBXModelBinaryFile;

class FBXModelSerializer
{
public:
	FBXModelSerializer();
	~FBXModelSerializer();

	void SaveBinaryFileFBX(FBXModel* _originModel, std::vector<MaterialDesc>& _materialDesc, const char* _filePath);

private:
private:
	///---------------------------------
	///��ü ��
	///---------------------------------
	// 1. binary�� ���� �������� ���ο� ����ü(FBXModelBinaryFile)�� ��´�.
	void OrganizeFBXModelFile(FBXModel* _originModel, std::vector<MaterialDesc>& _materialDesc);
	// 2. m_DataFile�� ����ȭ�ϰ� binary ���Ϸ� ���� ��������
	void WriteBinarayFile(const char* _filePath);
	// 3. txt ������ ����
	void WriteTextFile(const char* _filePath);

	///---------------------------------
	///Organize
	///---------------------------------
	/// ���
	void OrganizeFBXModelHeader(FBXModel* _originModel, std::vector<MaterialDesc>& _materialDesc);
	
	void OrganizeHeaderMesh(FBXModel* _originModel);
	void OrganizeHeaderMaterial(FBXModel* _originModel, std::vector<MaterialDesc>& _materialDesc);
	void OrganizeHeaderSkeleton(FBXModel* _originModel);
	void OrganizeHeaderAnimation(FBXModel* _originModel);

	/// ������
	void OrganizeFBXModelData(FBXModel* _originModel, std::vector<MaterialDesc>& _materialDesc);
	
	void OrganizeDataMesh(FBXModel* _originModel);
	void OrganizeDataMaterial(std::vector<MaterialDesc>& _materialDesc);
	void OrganizeDataSkeleton(FBXModel* _originModel);
	void OrganizeDataAnimation(FBXModel* _originModel);

	///---------------------------------
	///Write
	///---------------------------------
	/// ���
	void WriteBinarayHeaderFile(std::ofstream* _out);
	/// ������
	void WriteBinarayDataFile(std::ofstream* _out);

private:
	///---------------------------------
	/// �ִϸ��̼� ����
	///---------------------------------
	//void OrganizeAnim(FBXModel* _originModel);
	//void WriteAnimFile(const char* _filePath, FBXModel* _originModel);

private:
	std::unique_ptr<FBXModelBinaryFile> m_DataFile;
};

