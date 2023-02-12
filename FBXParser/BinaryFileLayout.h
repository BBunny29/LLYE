#pragma once
#include <vector> 
#include <typeinfo>

#include "VertexHelper.h"	// ���ҽ��Ŵ���
#include "MaterialData.h"	// ���ҽ��Ŵ��� 
#include "simpleMath.h"
#include "optMath.h"

/// <summary>
/// ���̳ʸ��� �ѱ� �������� ��Ƴ��� ����ü
/// "���" �� "������"�� �������ִ�. 
/// 
/// �������� ����(struct FBXModel) -> 
///
/// 2022. 11. 26  B.Bunny
/// </summary>

#pragma region FBXModel

/// ---------------------------------------------------
/// �� ����ü
/// ---------------------------------------------------

/// ���-----------------------------------------------
struct FBXModelBinaryFileHeader
{
	// �Ž�
	int meshCount = 0;

	std::vector<int> vertexCount_V;
	std::vector<int> indexCount_V;

	VertexType vertexType;

	// ���׸���
	bool isMaterial = false;
	size_t materialCount = 0;								// ���׸��� ����
	std::vector<int> materialNameLength_V;					// ���׸����� �̸��� ����
	std::vector<int> textureNameCount_V;					// ���׸��� ���ӵǾ��ִ� �ؽ��ĵ��� ����
	std::vector<std::vector<int>> textureNameLength_V;		// ���׸��� ���ӵǾ��ִ� �ؽ��ĵ��� �̸��� ����
	std::vector<int> materialMapping_V;						// ���׸����� �ε���


	// ���̷���(Bone)
	bool isSkeleton = false;
	size_t boneCount = 0;									// �� ����
	size_t boneOffsetCount = 0;								// �������� ����
	std::vector<int> boneNameLength_V;						// ���̸� ����

	// �ִϸ��̼� ����
	bool isSkinnedAnimation = false;
	bool isMeshAnimation = false;
	size_t aniCount;										// �ִϸ��̼� ����
	std::vector<int> aniNameLength;							// �ִ� �̸� ����
	std::vector<int> animationKeyFrameCount_V;				// �ִ� Ű������ ����
};

/// ������---------------------------------------------
//struct AnimationBinaryData
//{
//	AnimationBinaryData() :
//		animationName(""), ticksPerFrame(0), totalKeyFrames(0), animationKeyFrame(0)
//	{
//
//	}
//
//	~AnimationBinaryData() {}
//
//	std::string								animationName;
//	float									ticksPerFrame;
//	unsigned int							totalKeyFrames;
//	std::vector<std::vector<Float4x4>>		animationKeyFrame;
//};
///

struct BoneBinaryData
{
	BoneBinaryData()
		: boneName(""), boneIndex(0), parentBoneIndex(0), bindPoseTransform(Float4x4()), worldTM(Float4x4()), localTM(Float4x4())
	{}

	~BoneBinaryData() {}

	std::string		boneName;
	int				boneIndex;
	int				parentBoneIndex;

	Float4x4		bindPoseTransform;
	Float4x4		worldTM;
	Float4x4		localTM;
};

struct SkeletonBinaryData
{
	std::vector<BoneBinaryData> bone_V;
	std::vector<Float4x4> boneOffset_V;
};

struct MeshBinaryFileData
{
	std::vector<Vertex::SerializerVertex> vertex_V;
	std::vector<DWORD> index_V;

	int meshIndex;
	bool isParent;
	int parentIndex;

	Float4x4		meshWorldTM;
	Float4x4		meshLocalTM;
};

struct FBXModelBinaryFileData
{
	std::vector<MeshBinaryFileData> mesh_V;
	std::vector<MaterialDesc> material_V;

	SkeletonBinaryData skeleton;
	//std::vector<AnimationBinaryData> animation_V;
};

///
struct FBXModelBinaryFile
{
	FBXModelBinaryFileHeader binHeader;
	FBXModelBinaryFileData binData;
};


/// ---------------------------------------------------
/// �ִϸ��̼� ����ü
/// ---------------------------------------------------
//struct AnimFileHeader
//{
//	// �ִϸ��̼� ����
//	bool isSkinnedAnimation = false;
//	bool isMeshAnimation = false;
//	bool isSkeleton = false;
//	size_t boneCount = 0;					// �� ����
//	size_t meshCount = 0;					// ���׸��� ����
//	int aniNameLength;						// �ִ� �̸� ����
//	int animationKeyFrameCount;				// �ִ� Ű������ ����
//};
//
//struct AnimFileForWrite
//{
//	std::vector<AnimFileHeader> animHeader;
//	std::vector <AnimationBinaryData> animData;
//};
//
//struct AnimFileForRead
//{
//	AnimFileHeader animHeader;
//	AnimationBinaryData animData;
//};

/// ---------------------------------------------------
/// ���׸��� ����ü
/// ---------------------------------------------------

//struct MatFileHeader
//{
//	int materialNameLength;
//
//	int albedoMapNameLength;
//	int normalMapNameLength;
//	int metalRoughMapNameLength;
//	int emissiveMapNameLength;
//};
//
//struct MatFileData
//{
//	std::string materialName;						// ��
//
//	std::string albedoMap;							// ��
//	std::string normalMap;							// ��
//	std::string metalRoughMap;						// ��
//	std::string emissiveMap;						// ��
//
//	float metallic;									// ��
//	float shineness;								// �� 
//	float normalFactor;
//	float emissiveFactor;
//
//	bool isTransparency;							// �� 
//
//};
//
//struct MatFile
//{
//	MatFileHeader matHeader;
//	MatFileData matData;
//};

#pragma endregion FBXModel
