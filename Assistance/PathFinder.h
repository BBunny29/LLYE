#pragma once
#include <string>

/// <summary>
/// ��ΰ� ��ȿ���� �˻��ϴ� Ŭ����
/// ��ΰ� ��ȿ���� ������(�װ��� ã�����ϴ� ���϶Ǵ� ������ ������) 
/// ���ΰ�θ� �˷��ְ� ���ΰ�ο� �α������� �����.  
/// 
/// 2022.08.20 B.Bunny
/// </summary>
class PathFinder
{
public:
	PathFinder() {};
	~PathFinder() {};

	static bool IsPathExist(std::string& path);

};

