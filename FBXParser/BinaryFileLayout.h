#pragma once
#include <vector> 
#include <typeinfo>

#include "VertexHelper.h"	// 리소스매니저
#include "MaterialData.h"	// 리소스매니저 
#include "simpleMath.h"
#include "optMath.h"

/// <summary>
/// 바이너리로 넘길 정보들을 담아놓는 구조체
/// "헤더" 와 "데이터"로 나눠줘있다. 
/// 
/// 오리지널 정보(struct FBXModel) -> 
///
/// 2022. 11. 26  B.Bunny
/// </summary>

#pragma region FBXModel

/// ---------------------------------------------------
/// 모델 구조체
/// ---------------------------------------------------

/// 헤더-----------------------------------------------
struct FBXModelBinaryFileHeader
{
	// 매쉬
	int meshCount = 0;

	std::vector<int> vertexCount_V;
	std::vector<int> indexCount_V;

	VertexType vertexType;

	// 머테리얼
	bool isMaterial = false;
	size_t materialCount = 0;								// 머테리얼 개수
	std::vector<int> materialNameLength_V;					// 머테리얼의 이름의 길이
	std::vector<int> textureNameCount_V;					// 머테리얼에 종속되어있는 텍스쳐들의 갯수
	std::vector<std::vector<int>> textureNameLength_V;		// 머테리얼에 종속되어있는 텍스쳐들의 이름의 길이
	std::vector<int> materialMapping_V;						// 머테리얼의 인덱스


	// 스켈레톤(Bone)
	bool isSkeleton = false;
	size_t boneCount = 0;									// 본 개수
	size_t boneOffsetCount = 0;								// 본오프셋 개수
	std::vector<int> boneNameLength_V;						// 뼈이름 길이

	// 애니메이션 정보
	bool isSkinnedAnimation = false;
	bool isMeshAnimation = false;
	size_t aniCount;										// 애니메이션 개수
	std::vector<int> aniNameLength;							// 애니 이름 길이
	std::vector<int> animationKeyFrameCount_V;				// 애니 키프레임 갯수
};

/// 데이터---------------------------------------------
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
/// 애니메이션 구조체
/// ---------------------------------------------------
//struct AnimFileHeader
//{
//	// 애니메이션 정보
//	bool isSkinnedAnimation = false;
//	bool isMeshAnimation = false;
//	bool isSkeleton = false;
//	size_t boneCount = 0;					// 뼈 개수
//	size_t meshCount = 0;					// 머테리얼 개수
//	int aniNameLength;						// 애니 이름 길이
//	int animationKeyFrameCount;				// 애니 키프레임 갯수
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
/// 머테리얼 구조체
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
//	std::string materialName;						// ★
//
//	std::string albedoMap;							// ★
//	std::string normalMap;							// ★
//	std::string metalRoughMap;						// ★
//	std::string emissiveMap;						// ★
//
//	float metallic;									// ★
//	float shineness;								// ★ 
//	float normalFactor;
//	float emissiveFactor;
//
//	bool isTransparency;							// ★ 
//
//};
//
//struct MatFile
//{
//	MatFileHeader matHeader;
//	MatFileData matData;
//};

#pragma endregion FBXModel
