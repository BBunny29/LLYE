#pragma once
#include <string>
#include <vector>
#include <queue>

/// <summary>
/// 
/// ���������� ��� �����͵��� ��θ��� �о�ͼ� ����
/// 
/// </summary>
class FileNameReader
{
public:
	static void SetRootFolder(std::string path);

	static std::vector<std::string>& GetBinName();

private:
	static std::vector<std::string> m_BinName;


};

