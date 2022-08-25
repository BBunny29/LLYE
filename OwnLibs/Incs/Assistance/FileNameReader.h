#pragma once
#include <string>
#include <vector>

/// <summary>
/// 정보폴더의 모든 데이터들의 경로명을 읽어와서 저장
/// 한번만 사용될수있게 설계했다.
/// 
/// 2022.08.11 B.Bunny
/// </summary>
class FileNameReader
{
public:
	FileNameReader() { isSet = false; };
	~FileNameReader() {};

	static bool SetRootFolder(std::string& _rootPath);

	static std::vector<std::string>& GetTextureNames();
	static std::vector<std::string>& GetMeshNames();
	static std::vector<std::string>& GetShaderNames();

	static std::vector<std::string>& GetBinNames();
	static std::vector<std::string>& GetAnimNames();
	static std::vector<std::string>& GetMatNames();

private:
	static void StoreAllFile(std::string& _path);

	static bool isSet;	// SetRootFolder함수가 한번 사용되었으면 true

	static std::vector<std::string> m_TextureNames;	// .png, .jpg, .dds, .bmp, .tga, hdr, .tif
	static std::vector<std::string> m_MeshNames;	// .fbx, .ase
	static std::vector<std::string> m_ShaderNames;	// .cso

	static std::vector<std::string> m_BinNames;		// .bin
	static std::vector<std::string> m_AnimNames;	// .Anim
	static std::vector<std::string> m_MatNames;		// .Mat


};

