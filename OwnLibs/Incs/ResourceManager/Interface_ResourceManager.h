#pragma once
#include "Enum_ResourceManager.h"
__interface IRenderer;

/// <summary>
/// ���ҽ� �Ŵ����� �������̽�(������)
/// ���� ������ ������ �ְ� �������� �Ѱ��ش�.
/// ���ҽ���(�Ž�����, ��Ʈ���� ����, �ؽ��� ����, ���̴� ����)�� �����ϰ� �ְ� 
/// ���ӿ������� String�̳� �ε����� ���ҽ��� �˻��� �������� �Ѱ� �ִ� ������ �ַ��Ѵ�.
/// �ٱ��κ�(���� ����)���� ����� �Լ��鸸 �����Լ��� �����.
/// 
/// 2022.09.16 B.Bunny
/// </summary>

__interface IResourceManager
{
public:
	virtual bool Initialize(std::shared_ptr<IRenderer> pRenderer) abstract;

	virtual int GetInfo() abstract;


};