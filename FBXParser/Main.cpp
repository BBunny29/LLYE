/// -------------------------------------
/// 프로젝트 FBXParser
/// 
/// FBX파일의 모델정보를 읽는 역할
/// Resource매니저로 정보를 넘길거다.
/// -------------------------------------
#include "pch.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "FBXParserLibraryDefine.h"
#include "FBXParser.h"

#ifdef _DEBUG
std::string RESOURCE_PATH = "../../Data/";
std::string WRITE_PATH = "../Data/";
#else
std::string RESOURCE_PATH = "../Data/";
std::string WRITE_PATH = "../Data/";
#endif

int main()
{
	/// Assist 라이브러리 실험실

	std::string _sa = "디버깅 스트링 테스트";
	std::string _sb = "Debuging string test";

	DebugString::PDS("%s %s", _sa.c_str(), _sb.c_str());
	DebugString::PDS("잘된다^0^");
	DebugString::PDS_LOG;

	//HRESULT hr = S_OK;
	HRESULT hr = E_INVALIDARG;

	try
	{
		//COM_ERROR_IF_FAILED(hr, "First Error");
		//
		//hr = DV_E_DVASPECT;
		//COM_ERROR_IF_FAILED(hr, "Second Error");
		//COM_ERROR_IF_FAILED(hr, "Third Error");
		//int i = 0;
		//std::string a = "aabb";
	}
	catch (COMException& exception1)
	{
		ErrorLogger::Log(exception1);
		return -1;
	}

	//assert(true);
	//assert(hr);

	if(SUCCEEDED(hr))
	{
		int i = 0;
	}
	else if (FAILED(hr))
	{
		int i = 0;
	}

	// 경로 검사
	if (PathFinder::IsPathExist(RESOURCE_PATH) == false)
	{
		return 0;
	}

	FileNameReader::SetRootFolder(RESOURCE_PATH);

	/// Assist 라이브러리 실험실

	// FBX파서 생성과 초기화
	FBXParser* _FBXParser = new FBXParser();
	_FBXParser->Initalize();

	// 임시
	std::string fileName = "../LulupinYeouiju/Data/Beaker01.fbx";

	// 경로가 있는지 확인
	bool _isPathExist = std::filesystem::exists(RESOURCE_PATH);

	// 없는경로면 
	if (_isPathExist == false)
	{
		std::cout << "path not exist" << std::endl;
		// 만약 파일이 없다면
		// 경고창 발생
		// 제일 첫번째 경로에 로그파일을 남길것이다.

		//std::string _fullName("");
		//_fullName.append("This.txt");
		//
		//std::ofstream _binaryFile(_fullName.c_str(), std::ios::out | std::ios::binary);
		//
		//if (_binaryFile.is_open())
		//{
		//	_binaryFile << "=======================================================" << "\n";
		//	_binaryFile << "Here" << "\n";
		//	_binaryFile << "=======================================================" << "\n";
		//}
		//
		//_binaryFile.close();
	}
	else
	{
		std::cout << "path exist" << std::endl;

		// 파일 이름들을 읽어들여온다.
		std::vector<std::string> _MeshFiles;
		// 각 파일들을 로드한다
		//for (std::string& _nowName : _MeshFiles)
		//{
		//	_FBXParser->LoadScene(_nowName, WRITE_PATH);
		_FBXParser->LoadScene(fileName, WRITE_PATH);
		//}
	}
	int i;
	std::cin >> i;
	_FBXParser->Destroy();
}