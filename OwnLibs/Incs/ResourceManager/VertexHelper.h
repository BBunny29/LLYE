/// 정리 完 (22.10.21)

#pragma once

#include <DirectXMath.h>
#include <d3d11.h>

using namespace DirectX;

enum class VertexType
{
	Type_VertexPos,
	Type_VertexPosNormal,
	Type_Vertex2D,
	Type_VertexColor,
	Type_VertexColorNormal,
	Type_VertexColorTexture,
	Type_Vertex,
	Type_VertexTangent,
	Type_VertexSkinned,
	Type_VertexSkinnedTangent,
};

namespace Vertex
{
	/// 시리얼라이즈용 버텍스
	struct SerializerVertex
	{
		SerializerVertex()
			: pos(0, 0, 0), texCoord(0, 0), normal(0, 0, 0), weights(0, 0, 0), rgba(0, 0, 0, 0), tangent(0, 0, 0, 0)
		{
			boneIndices[0] = 0;
			boneIndices[1] = 0;
			boneIndices[2] = 0;
			boneIndices[3] = 0;
		};

		SerializerVertex(float x, float y, float z,
			float nx, float ny, float nz,
			float u, float v,
			float w1, float w2, float w3,
			float r, float g, float b, float a,
			float tx, float ty, float tz, float tw,
			BYTE indx1, BYTE indx2, BYTE indx3, BYTE indx4)
			: pos(x, y, z), normal(nx, ny, nz), texCoord(u, v), weights(w1, w2, w3), rgba(r, g, b, a),
			tangent(tx, ty, tz, tw)
		{
			boneIndices[0] = indx1;
			boneIndices[1] = indx2;
			boneIndices[2] = indx3;
			boneIndices[3] = indx4;
		};

		XMFLOAT3 pos;
		XMFLOAT4 rgba;
		XMFLOAT2 texCoord;
		XMFLOAT3 normal;
		XMFLOAT4 tangent;
		XMFLOAT3 weights;
		UINT boneIndices[4];
	};

	struct VertexPos
	{
		VertexPos()
			: pos(0, 0, 0)
		{}

		VertexPos(float x, float y, float z)
			: pos(x, y, z) {}
		XMFLOAT3 pos;
	};

	struct VertexPosNormal
	{
		VertexPosNormal()
			: pos(0, 0, 0)
			, normal(0, 0, 0)
		{}

		VertexPosNormal(float x, float y, float z, float nx, float ny, float nz)
			: pos(x, y, z)
			, normal(nx, ny, nz)
		{}
		XMFLOAT3 pos;
		XMFLOAT3 normal;
	};

	struct Vertex2D
	{
		Vertex2D()
			: pos(0, 0, 0), texCoord(0, 0)
		{}

		Vertex2D(float x, float y, float z, float u, float v)
			: pos(x, y, z), texCoord(u, v) {}

		XMFLOAT3 pos;
		XMFLOAT2 texCoord;
	};

	struct VertexColor
	{
		VertexColor()
			: pos(0, 0, 0), rgba(0, 0, 0, 0)
		{ }
		VertexColor(float x, float y, float z,
			float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f)
			: pos(x, y, z), rgba(r, g, b, a) {}

		VertexColor(XMFLOAT3 _pos, XMFLOAT4 _color) :
			pos(_pos), rgba(_color) {};

		XMFLOAT3 pos;
		XMFLOAT4 rgba;
	};

	struct VertexColorNormal
	{
		VertexColorNormal()
			: pos(0, 0, 0), normal(0, 0, 0), rgba(0, 0, 0, 0)
		{}
		VertexColorNormal(float x, float y, float z,
			float nx, float ny, float nz,
			float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f)
			: pos(x, y, z), normal(nx, ny, nz), rgba(r, g, b, a) {}

		XMFLOAT3 pos;
		XMFLOAT4 rgba;
		XMFLOAT3 normal;
	};

	struct VertexColorTexture
	{
		VertexColorTexture()
			: pos(0, 0, 0), rgba(0, 0, 0, 0), texCoord(0, 0)
		{}
		VertexColorTexture(float x, float y, float z,
			float u, float v,
			float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f)
			: pos(x, y, z), rgba(r, g, b, a), texCoord(u, v) {}

		XMFLOAT3 pos;
		XMFLOAT4 rgba;
		XMFLOAT2 texCoord;
	};

	struct Vertex
	{
		Vertex()
			: pos(0, 0, 0), normal(0, 0, 0), texCoord(0, 0)
		{}

		Vertex(float x, float y, float z,
			float nx, float ny, float nz,
			float u, float v,
			float tx, float ty, float tz)
			: pos(x, y, z), normal(nx, ny, nz), texCoord(u, v) {}

		XMFLOAT3 pos;
		XMFLOAT3 normal;
		XMFLOAT2 texCoord;
	};

	struct VertexTangent
	{
		VertexTangent()
			:pos(0.0f, 0.0f, 0.0f), normal(0.0f, 0.0f, 0.0f), texCoord(0.0f, 0.0f), tangent(0.0f, 0.0f, 0.0f) {}
		VertexTangent(const XMFLOAT3& p, const XMFLOAT3& n, const XMFLOAT3& t, const XMFLOAT2& uv)
			: pos(p), normal(n), texCoord(uv), tangent(t) {}
		VertexTangent(
			float px, float py, float pz,
			float nx, float ny, float nz,
			float tx, float ty, float tz,
			float u, float v)
			: pos(px, py, pz), normal(nx, ny, nz), texCoord(u, v), tangent(tx, ty, tz) {}

		XMFLOAT3 pos;
		XMFLOAT3 normal;
		XMFLOAT2 texCoord;
		XMFLOAT3 tangent;
	};

	struct VertexSkinned
	{
		VertexSkinned()
			: pos(0, 0, 0), texCoord(0, 0), normal(0, 0, 0), weights()
		{
			boneIndices[0] = 0;
			boneIndices[1] = 0;
			boneIndices[2] = 0;
			boneIndices[3] = 0;
		};

		VertexSkinned(float x, float y, float z,
			float nx, float ny, float nz,
			float u, float v,
			float w1, float w2, float w3,
			BYTE indx1, BYTE indx2, BYTE indx3, BYTE indx4)
			: pos(x, y, z), normal(nx, ny, nz), texCoord(u, v), weights()
		{
			boneIndices[0] = indx1;
			boneIndices[1] = indx2;
			boneIndices[2] = indx3;
			boneIndices[3] = indx4;
		};

		XMFLOAT3 pos;
		XMFLOAT3 normal;
		XMFLOAT2 texCoord;
		FLOAT weights[4];
		UINT boneIndices[4];
	};

	struct VertexSkinnedTangent
	{
		VertexSkinnedTangent()
			: pos(0, 0, 0), normal(0, 0, 0), texCoord(0, 0), tangent(0, 0, 0, 0), weights()
		{
			boneIndices[0] = 0;
			boneIndices[1] = 0;
			boneIndices[2] = 0;
			boneIndices[3] = 0;
		};

		VertexSkinnedTangent(float x, float y, float z,
			float nx, float ny, float nz,
			float u, float v,
			float w1, float w2, float w3,
			BYTE indx1, BYTE indx2, BYTE indx3, BYTE indx4)
			: pos(x, y, z), normal(nx, ny, nz), texCoord(u, v), tangent(0, 0, 0, 0), weights()
		{
			boneIndices[0] = indx1;
			boneIndices[1] = indx2;
			boneIndices[2] = indx3;
			boneIndices[3] = indx4;
		};

		XMFLOAT3 pos;
		XMFLOAT3 normal;
		XMFLOAT2 texCoord;
		XMFLOAT4 tangent;
		FLOAT weights[4];
		UINT boneIndices[4];
	};

}

