#include "pch.h"
#include "FileNameReader.h"

std::vector<std::string> FileNameReader::m_BinName;


void FileNameReader::SetRootFolder(std::string path)
{
}

std::vector<std::string>& FileNameReader::GetBinName()
{
	return m_BinName;
}
