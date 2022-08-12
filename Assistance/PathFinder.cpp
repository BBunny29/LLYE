#include "pch.h"
#include "PathFinder.h"
#include "DebugString.h"
#include "ErrorLogger.h"

#include <filesystem>
#include <fstream>

bool PathFinder::IsPathExist(std::string& path)
{
#ifdef _WIN64
	#ifdef _DEBUG
		std::string _curFormat = "x64Debug";
	#else
		std::string _curFormat = "x64Release";
	#endif
#else
	#ifdef _DEBUG
		std::string _curFormat = "x86Debug";
	#else
		std::string _curFormat = "x86Release";
	#endif
#endif

	bool _isPathExist = std::filesystem::exists(path);
	
	// 경로가 없으면 
	if (_isPathExist == false)
	{
		// 1. Log txt파일 출력
		std::string _RootName("This is RootPoint.txt");
		
		std::ofstream _binaryFile(_RootName.c_str(), std::ios::out);
		if (_binaryFile.is_open())
		{
			_binaryFile << "=======================================================" << "\n";
			_binaryFile << "Here I Am" << "\n";
			_binaryFile << _curFormat << "\n";		
			_binaryFile << std::filesystem::current_path().string() << "\n"; // 경로도 같이 출력
			_binaryFile << "=======================================================" << "\n";
		}
		_binaryFile.close();

		std::string _curPath = "path does not exist \nCurrent Root Path : ";
		_curPath.append(std::filesystem::current_path().string());

		// 2. Debug String 출력
		DebugString::PDS("%s", _curPath.c_str());
		
		// 3. 경고창 출력(메세지 박스)
		ErrorLogger::Log(_curPath, ErrorKind::ePath);
	}

	return _isPathExist;
}
