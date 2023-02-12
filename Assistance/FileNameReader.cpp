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
	//�̹� �ѹ� ���Ǿ����� �ٽ� ����Ҽ� ����.(�ַ���� ���������� �ѹ��� ���Ǿ��Ѵ�.)
	if (isSet != false)
	{
		return false;
	}

	// ��� ���
	std::cout << "��θ�� :" << std::endl;

	// ��Ʈ ���� �Ʒ��� ��� ��θ� �����´�.
	StoreAllFile(_rootPath);

	std::cout << "��θ�� ��\n" << std::endl;

	isSet = true;
	return true;
}

/// <summary>
/// ��� �Ʒ��� ��� ���ϰ� ������ ���ڿ��� �о���̰� �з��Ѵ�.
/// </summary>
/// <param name="_path"></param>
void FileNameReader::StoreAllFile(std::string& _path)
{
	for (const auto& file : std::filesystem::directory_iterator(_path))
	{		
		// �����϶� ��͸� ����.
		if (std::filesystem::is_directory(file.path()))
		{
			std::string curFolder = file.path().string() + "/";
			std::cout << curFolder << std::endl;

			StoreAllFile(curFolder);
		}
		// �����϶�
		else if (std::filesystem::is_regular_file(file.path()))
		{
			std::string curFilePath = file.path().string();
			std::cout << curFilePath << std::endl;

			std::string extension;

			for (size_t i = curFilePath.size() - 1; i > 0; i--)
			{
				if (curFilePath.at(i) == '.')
				{
					// ��ο��� Ȯ���ڸ� �߶󳽴�.
					extension = curFilePath.substr(i, curFilePath.size() - i);

					// Ȯ���� ���� ��� ���� �ڿ� �������� �˻��Ѵ�.
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

