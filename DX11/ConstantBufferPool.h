#pragma once

/// 렌더 패스에 넘겨줄 다양한 상수버퍼들을 관리해주는 클래스
/// 만든 이유는 다음과 같다
/// 헬퍼(그리드 등) 추가 이후, 그림을 그릴 때 해당 클래스의 내부에서 처리를 하고 싶었다.
/// 이때, 헬퍼 자신을 그리기 위한 상수 버퍼를 넘겨줄 필요가 생겼다.
/// 현재 구조에서 해당 함수가 호출될 때 인자로 상수버퍼를 넘겨줘야하게 되었는데,
/// 그렇게 될 경우 원치 않게 헬퍼의 헤더가 상수버퍼의 헤더를 참조하는 경우가 발생했다.
/// 이 구조를 어떻게 할지 생각을 하다가 차라리 전역적으로 접근 가능한 클래스로 처리하자는 아이디어로 발전
/// RasterizerState도 이와 같은 형식으로 사용중에 있다.

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

