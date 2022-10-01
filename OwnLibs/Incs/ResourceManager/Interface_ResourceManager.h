#pragma once
#include "Enum_ResourceManager.h"
/// �ܺ� ������Ʈ�� ����� EngineBB�� �������̽��鸸 ��Ƴ��� .h

/// <summary>
/// ���ҽ� �Ŵ����� �������̽�(������)
/// �ٱ��κ�(���� ����)���� ����� �Լ��鸸 �����Լ��� �����.
/// 
/// 2022.09.16 B.Bunny
/// </summary>

__interface IResourceManager
{
public:
	virtual bool Initialize() abstract;

	virtual int GetInfo() abstract;


};