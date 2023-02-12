#pragma once
#include "Enum_ResourceManager.h"
__interface IRenderer;

/// <summary>
/// 리소스 매니저의 인터페이스(껍데기)
/// 게임 엔진이 가지고 있고 렌더러에 넘겨준다.
/// 리소스들(매쉬정보, 머트리얼 정보, 텍스쳐 정보, 쉐이더 정보)을 저장하고 있고 
/// 게임엔진에서 String이나 인덱스로 리소스를 검색해 렌더러로 넘겨 주는 역할을 주로한다.
/// 바깥부분(게임 엔진)에서 사용할 함수들만 가상함수로 만든다.
/// 
/// 2022.09.16 B.Bunny
/// </summary>

__interface IResourceManager
{
public:
	virtual bool Initialize(std::shared_ptr<IRenderer> pRenderer) abstract;

	virtual int GetInfo() abstract;


};