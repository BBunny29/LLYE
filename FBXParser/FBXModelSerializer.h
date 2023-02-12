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
	///전체 모델
	///---------------------------------
	// 1. binary로 만들 모델정보를 새로운 구조체(FBXModelBinaryFile)에 담는다.
	void OrganizeFBXModelFile(FBXModel* _originModel, std::vector<MaterialDesc>& _materialDesc);
	// 2. m_DataFile를 직렬화하고 binary 파일로 만들어서 내보낸다
	void WriteBinarayFile(const char* _filePath);
	// 3. txt 파일을 쓴다
	void WriteTextFile(const char* _filePath);

	///---------------------------------
	///Organize
	///---------------------------------
	/// 헤더
	void OrganizeFBXModelHeader(FBXModel* _originModel, std::vector<MaterialDesc>& _materialDesc);
	
	void OrganizeHeaderMesh(FBXModel* _originModel);
	void OrganizeHeaderMaterial(FBXModel* _originModel, std::vector<MaterialDesc>& _materialDesc);
	void OrganizeHeaderSkeleton(FBXModel* _originModel);
	void OrganizeHeaderAnimation(FBXModel* _originModel);

	/// 데이터
	void OrganizeFBXModelData(FBXModel* _originModel, std::vector<MaterialDesc>& _materialDesc);
	
	void OrganizeDataMesh(FBXModel* _originModel);
	void OrganizeDataMaterial(std::vector<MaterialDesc>& _materialDesc);
	void OrganizeDataSkeleton(FBXModel* _originModel);
	void OrganizeDataAnimation(FBXModel* _originModel);

	///---------------------------------
	///Write
	///---------------------------------
	/// 헤더
	void WriteBinarayHeaderFile(std::ofstream* _out);
	/// 데이터
	void WriteBinarayDataFile(std::ofstream* _out);

private:
	///---------------------------------
	/// 애니메이션 정보
	///---------------------------------
	//void OrganizeAnim(FBXModel* _originModel);
	//void WriteAnimFile(const char* _filePath, FBXModel* _originModel);

private:
	std::unique_ptr<FBXModelBinaryFile> m_DataFile;
};

