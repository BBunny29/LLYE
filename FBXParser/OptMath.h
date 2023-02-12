#pragma once

/// <summary>
/// 생성자가 없는 자체 매트릭스 컨테이너 구초체
/// 파싱후 시리얼라이제이션을 할때 사용한다.
/// 
/// 
/// </summary>

struct Float4x4
{
	union
	{
		struct
		{
			float m00, m01, m02, m03;
			float m10, m11, m12, m13;
			float m20, m21, m22, m23;
			float m30, m31, m32, m33;
		};
		float m[4][4];
	};
};

struct Float4x4Func : public Float4x4
{
	Float4x4Func() {};
	Float4x4Func(const Float4x4& float4x4)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				this->m[i][j] = float4x4.m[i][j];
			}
		}
	}
	Float4x4Func(float f00, float f01, float f02, float f03,
		float f10, float f11, float f12, float f13,
		float f20, float f21, float f22, float f23,
		float f30, float f31, float f32, float f33)
	{
		this->m00 = f00; this->m01 = f01; this->m02 = f02; this->m03 = f03;

		this->m10 = f10; this->m11 = f11;
		this->m12 = f12;
		this->m13 = f13;

		this->m20 = f20;
		this->m21 = f21;
		this->m22 = f22;
		this->m23 = f23;

		this->m30 = f30;
		this->m31 = f31;
		this->m32 = f32;
		this->m33 = f33;
	}
	Float4x4& operator=(const Float4x4& float4x4)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				this->m[i][j] = float4x4.m[i][j];
			}
		}

		return *this;
	}
	Float4x4& operator=(const DirectX::SimpleMath::Matrix& float4x4)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				this->m[i][j] = float4x4.m[i][j];
			}
		}

		return *this;
	}
	Float4x4 operator+(Float4x4& float4x4)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				this->m[i][j] += float4x4.m[i][j];
			}
		}

		return *this;
	}
	Float4x4 operator-(Float4x4& float4x4)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				this->m[i][j] -= float4x4.m[i][j];
			}
		}

		return *this;
	}
	bool operator==(Float4x4& float4x4)
	{
		if (this->m00 == float4x4.m00 && this->m01 == float4x4.m01 && this->m02 == float4x4.m02 && this->m03 == float4x4.m03
			&& this->m10 == float4x4.m10 && this->m11 == float4x4.m11 && this->m12 == float4x4.m12 && this->m13 == float4x4.m13
			&& this->m20 == float4x4.m20 && this->m21 == float4x4.m21 && this->m22 == float4x4.m22 && this->m23 == float4x4.m23
			&& this->m30 == float4x4.m30 && this->m31 == float4x4.m31 && this->m32 == float4x4.m32 && this->m33 == float4x4.m33)
		{
			return true;
		}
		return false;

	}
	bool operator!=(Float4x4& float4x4)
	{
		if (this->m00 != float4x4.m00 || this->m01 != float4x4.m01 || this->m02 != float4x4.m02 || this->m03 != float4x4.m03
			|| this->m10 != float4x4.m10 || this->m11 != float4x4.m11 || this->m12 != float4x4.m12 || this->m13 != float4x4.m13
			|| this->m20 != float4x4.m20 || this->m21 != float4x4.m21 || this->m22 != float4x4.m22 || this->m23 != float4x4.m23
			|| this->m30 != float4x4.m30 || this->m31 != float4x4.m31 || this->m32 != float4x4.m32 || this->m33 != float4x4.m33)
		{
			return true;
		}
		return false;
	}
};