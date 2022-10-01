#pragma once
#include "align16.h"
#include <DirectXMath.h>

struct CB_VS_wvp : public AlignedAllocationPolicy<16>
{
	DirectX::XMMATRIX wvpMatrix;
};

struct CB_VS_wvpW : public AlignedAllocationPolicy<16>
{
	DirectX::XMMATRIX wvpMatrix;
	DirectX::XMMATRIX worldMatrix;
};

struct CB_VS_WVP : public AlignedAllocationPolicy<16>
{
	DirectX::XMMATRIX worldMatrix;
	DirectX::XMMATRIX viewMatrix;
	DirectX::XMMATRIX projectionMatrix;
};

struct CB_VS_1M : public AlignedAllocationPolicy<16>
{
	DirectX::XMMATRIX matrix1;
};

struct CB_VS_2M : public AlignedAllocationPolicy<16>
{
	DirectX::XMMATRIX matrix1;
	DirectX::XMMATRIX matrix2;
};

struct CB_VS_3M : public AlignedAllocationPolicy<16>
{
	DirectX::XMMATRIX matrix1;
	DirectX::XMMATRIX matrix2;
	DirectX::XMMATRIX matrix3;
};