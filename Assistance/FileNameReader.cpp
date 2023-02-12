#include "pch.h"
#include "FileNameReader.h"

#include <filesystem>
#include <iostream>

bool FileNameReader::isSet;

std::vector<std::string> FileNameReader::m_TextureNames;	// .png, .jpg, .dds, .bmp, .tga, hdr, .tif
std::vector<std::string> FileNameReader::m_MeshNames;		// .fbx, .ase
std::vector<std::string> FileNameReader::m_ShaderNames;		// .cso

std::vector<std::string> FileNameReader::m_BinNames;		// .bin
std::vector<std::string> FileNameReader::m_AnimNames;		// .anim
std::vector<std::string> FileNameReader::m_MatNames;		// .mat

bool FileNameReader::SetRootFolder(std::string& _rootPath)
{
	//이미 한번 사용되었으면 다시 사용할수 없다.(솔루션이 실행됬을때 한번만 사용되야한다.)
	if (isSet != false)
	{
		return false;
	}

	// 경로 목록
	std::cout << "경로목록 :" << std::endl;

	// 루트 폴더 아래의 모든 경로를 가져온다.
	StoreAllFile(_rootPath);

	std::cout << "경로목록 끝\n" << std::endl;

	isSet = true;
	return true;
}

/// <summary>
/// 경로 아래의 모든 파일과 폴더의 문자열을 읽어들이고 분류한다.
/// </summary>
/// <param name="_path"></param>
void FileNameReader::StoreAllFile(std::string& _path)
{
	for (const auto& file : std::filesystem::directory_iterator(_path))
	{		
		// 폴더일때 재귀를 돈다.
		if (std::filesystem::is_directory(file.path()))
		{
			std::string curFolder = file.path().string() + "/";
			std::cout << curFolder << std::endl;

			StoreAllFile(curFolder);
		}
		// 파일일때
		else if (std::filesystem::is_regular_file(file.path()))
		{
			std::string curFilePath = file.path().string();
			std::cout << curFilePath << std::endl;

			std::string extension;

			for (size_t i = curFilePath.size() - 1; i > 0; i--)
			{
				if (curFilePath.at(i) == '.')
				{
					// 경로에서 확장자명만 잘라낸다.
					extension = curFilePath.substr(i, curFilePath.size() - i);

					// 확장자 명을 모두 읽은 뒤에 대조군을 검사한다.
					if (extension == ".dds" || extension == ".png" || extension == ".hdr" ||
						extension == ".bmp" || extension == ".tif" || extension == ".jpg" ||
						extension == ".tga")
					{
						m_TextureNames.push_back(curFilePath);
					}
					else if (extension == ".fbx" || extension == ".ase" || extension == ".ASE")
					{
						m_MeshNames.push_back(curFilePath);
					}
					else if (extension == ".cso" || extension == ".fx" || extension == ".fxo")
					{
						m_ShaderNames.push_back(curFilePath);
					}
					else if (extension == ".bin")
					{
						m_BinNames.push_back(curFilePath);
					}
					else if (extension == ".anim")
					{
						m_AnimNames.push_back(curFilePath);
					}
					else if (extension == ".mat")
					{
						m_MatNames.push_back(curFilePath);
					}
				}
			}
		}
	}
}

std::vector<std::string>& FileNameReader::GetTextureNames()
{
	return m_TextureNames;
}

std::vector<std::string>& FileNameReader::GetMeshNames()
{
	return m_MeshNames;
}

std::vector<std::string>& FileNameReader::GetShaderNames()
{
	return m_ShaderNames;
}

std::vector<std::string>& FileNameReader::GetBinNames()
{
	return m_BinNames;
}

std::vector<std::string>& FileNameReader::GetAnimNames()
{
	return m_AnimNames;
}

std::vector<std::string>& FileNameReader::GetMatNames()
{
	return m_MatNames;
}

