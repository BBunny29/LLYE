#pragma once
#include <string>
#include <vector>
#include <queue>

/// <summary>
/// 
/// 정보폴더의 모든 데이터들의 경로명을 읽어와서 저장
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

