#pragma once

/// ���� �н��� �Ѱ��� �پ��� ������۵��� �������ִ� Ŭ����
/// ���� ������ ������ ����
/// ����(�׸��� ��) �߰� ����, �׸��� �׸� �� �ش� Ŭ������ ���ο��� ó���� �ϰ� �;���.
/// �̶�, ���� �ڽ��� �׸��� ���� ��� ���۸� �Ѱ��� �ʿ䰡 �����.
/// ���� �������� �ش� �Լ��� ȣ��� �� ���ڷ� ������۸� �Ѱ�����ϰ� �Ǿ��µ�,
/// �׷��� �� ��� ��ġ �ʰ� ������ ����� ��������� ����� �����ϴ� ��찡 �߻��ߴ�.
/// �� ������ ��� ���� ������ �ϴٰ� ���� ���������� ���� ������ Ŭ������ ó�����ڴ� ���̵��� ����
/// RasterizerState�� �̿� ���� �������� ����߿� �ִ�.

#include "ConstantBuffer.h"
#include <vector>

enum class CBufferType
{
	VS = 0,
	GS,
	PS,
	CS
};

enum class CBufferSize
{
	SIZE_4, SIZE_8, SIZE_12, SIZE_16, SIZE_20,
	SIZE_24, SIZE_28, SIZE_32, SIZE_36, SIZE_40,
	SIZE_44, SIZE_48, SIZE_52, SIZE_56, SIZE_60, SIZE_64,
};


class ConstantBufferPool
{
public:
	static void Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);

	static ConstantBuffer<CB_VS_WVP>* GetWVPMatrix();

	static ConstantBuffer<CB_VS_1M>* Get1Matrix();
	static ConstantBuffer<CB_VS_2M>* Get2Matrix();
	static ConstantBuffer<CB_VS_3M>* Get3Matrix();

private:
	static ConstantBuffer<CB_VS_WVP>* m_vs_WVPMatrix;

	static ConstantBuffer<CB_VS_1M>* m_vs_1Matrix;
	static ConstantBuffer<CB_VS_2M>* m_vs_2Matrix;
	static ConstantBuffer<CB_VS_3M>* m_vs_3Matrix;

};

