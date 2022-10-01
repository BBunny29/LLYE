#pragma once
#include "Enum_ResourceManager.h"
/// 외부 프로젝트와 연결될 EngineBB의 인터페이스들만 모아놓은 .h

/// <summary>
/// 리소스 매니저의 인터페이스(껍데기)
/// 바깥부분(게임 엔진)에서 사용할 함수들만 가상함수로 만든다.
/// 
/// 2022.09.16 B.Bunny
/// </summary>

__interface IResourceManager
{
public:
	virtual bool Initialize() abstract;

	virtual int GetInfo() abstract;


};