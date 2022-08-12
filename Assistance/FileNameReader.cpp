#include "pch.h"
#include "FileNameReader.h"

bool FileNameReader::isSet;

std::vector<std::string> FileNameReader::m_BinName;


bool FileNameReader::SetRootFolder(std::string& path)
{
	//이미 한번 사용되었으면 다시 사용할수 없다.(솔루션이 실행됬을때 한번만 사용되야한다.)
	if (isSet != false)
	{
		return false;
	}

	// 경로를 읽는다.


	isSet = true;
	return true;
}


std::vector<std::string>& FileNameReader::GetBinName()
{
	return m_BinName;
}
