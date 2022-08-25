#pragma once
#include <string>

/// <summary>
/// 경로가 유효한지 검사하는 클래스
/// 경로가 유효하지 않으면(그곳에 찾고자하는 파일또는 폴더가 없으면) 
/// 메인경로를 알려주고 메인경로에 로그파일을 남긴다.  
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

