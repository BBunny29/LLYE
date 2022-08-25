﻿/// -------------------------------------
/// 프로젝트 FBXParser
/// 
/// FBX파일의 모델정보를 읽는 역할
/// Resource매니저로 정보를 넘길거다.
/// -------------------------------------
#include "pch.h"
#include <filesystem>
#include <fstream>

#include "FBXParserLibraryDefine.h"
#include "FBXParser.h"
#include "FileNameReader.h"
#include "Timer.h"
#include "StringHelper.h"

#ifdef _DEBUG
std::string RESOURCE_PATH = "../Data/";
std::string WRITE_PATH = "../Data/";
#else
std::string RESOURCE_PATH = "../Data/";
std::string WRITE_PATH = "../Data/";
#endif

int main()
{
	/// Assist 라이브러리 실험실

	// stringHelper
	std::string a = RESOURCE_PATH + "apple.fbx";
	std::string b = StringHelper::GetFileName(a, true);
	std::string c = StringHelper::GetFileName(a, false);

	// Timer
	Stopwatch::InitTimer();

	for (int i = 0; i < 100; i++)
	{
		Stopwatch::StartMeasure(std::to_string(i));
	}

	for (int i = 0; i < 10000000; i++)
	{
	}

	for (int i = 0; i < 100; i++)
	{
		Stopwatch::StopMeasure(std::to_string(i));
	}

	Stopwatch::PrintResult();

	// DebugString
	std::string _sa = "디버깅 스트링 테스트";
	std::string _sb = "Debuging string test";

	DebugString::PDS("%s %s", _sa.c_str(), _sb.c_str());
	DebugString::PDS("잘된다^0^");
	DebugString::PDS_LOG;

	// ErrorLogger
	ERROR_BOX("ErrorTest");
	
	int* _i2 = nullptr;	
	ASSERT_NULLCHECK(_i2, "Assert test string!!!");
		
	HRESULT hr = S_OK;
	
	try
	{
		THROW_COM_ERROR_IF_FAILED(hr, "First Error");
		
		hr = E_INVALIDARG;
		THROW_COM_ERROR_IF_FAILED(hr, "Second Error");
		THROW_COM_ERROR_IF_FAILED(hr, "Third Error");

	}
	catch (COMException& exception1)
	{
		ErrorLogger::Log(exception1);
		return -1;
	}	

	assert(true);

	if(SUCCEEDED(hr))
	{
		int i = 0;
	}
	else if (FAILED(hr))
	{
		int i = 0;
	}
	
	/// ~Assist 라이브러리 실험실

	// 경로 검사
	if (PathFinder::IsPathExist(RESOURCE_PATH) == false)
	{
		return 0;
	}

	FileNameReader::SetRootFolder(RESOURCE_PATH);

	// FBX파서 생성과 초기화
	FBXParser* _FBXParser = new FBXParser();
	_FBXParser->Initalize();

	// 파일 이름들을 읽어들여온다.
	std::vector<std::string> _MeshFiles;
	_MeshFiles = FileNameReader::GetMeshNames();
	
	// 각 파일들을 로드한다
	for (std::string& _nowName : _MeshFiles)
	{
		_FBXParser->LoadScene(_nowName, WRITE_PATH);
	}

	//임시
	int i;
	std::cin >> i;
	_FBXParser->Destroy();
}