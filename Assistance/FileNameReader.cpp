#include "pch.h"
#include "FileNameReader.h"

bool FileNameReader::isSet;

std::vector<std::string> FileNameReader::m_BinName;


bool FileNameReader::SetRootFolder(std::string& path)
{
	//�̹� �ѹ� ���Ǿ����� �ٽ� ����Ҽ� ����.(�ַ���� ���������� �ѹ��� ���Ǿ��Ѵ�.)
	if (isSet != false)
	{
		return false;
	}

	// ��θ� �д´�.


	isSet = true;
	return true;
}


std::vector<std::string>& FileNameReader::GetBinName()
{
	return m_BinName;
}
