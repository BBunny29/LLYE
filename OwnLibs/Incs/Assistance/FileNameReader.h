#pragma once
#include <string>
#include <vector>
#include <queue>

/// <summary>
/// ���������� ��� �����͵��� ��θ��� �о�ͼ� ����
/// 
/// 2022.08.11 B.Bunny
/// </summary>
class FileNameReader
{
public:
	FileNameReader() { isSet = false; };
	~FileNameReader() {};

	static bool SetRootFolder(std::string& path);

	static std::vector<std::string>& GetBinName();

private:


	static bool isSet;	// SetRootFolder�Լ��� �ѹ� ���Ǿ����� true

	static std::vector<std::string> m_TextureNames;	// .png, .jpg, 
	static std::vector<std::string> m_MeshNames;
	static std::vector<std::string> m_ShaderNames;	// .hlsl, .cso

	static std::vector<std::string> m_BinName;		// .bin
	static std::vector<std::string> m_AnimNames;	// .Anim
	static std::vector<std::string> m_MatNames;		// .Mat

	static std::vector<std::string> m_IBLNames;
	static std::vector<std::string> m_BankNames;
	static std::vector<std::string> m_QuestNames;
	static std::vector<std::string> m_DialogueNames;
};

