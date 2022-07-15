/// ----------------------------------------------------
/// 2022.07.14 burnigbunny
/// 
/// 파서 재구축
/// ----------------------------------------------------
#include <string>
#include <memory>
#include "FBXParser.h"

#ifdef _DEBUG
std::string RESOURCE_PATH = "../../SeedVault/Data/model/";
std::string WRITE_PATH = "../../SeedVault/Data/bin/";
#else
std::string RESOURCE_PATH = "../Data/model/";
std::string WRITE_PATH = "../Data/bin/";
#endif

int main()
{
	FBXParser* _JMParser = new FBXParser();

	_JMParser->Initalize();

	for (std::string& _nowName : g_MeshNames)
	{
		_JMParser->LoadScene(_nowName, WRITE_PATH);
	}

	_JMParser->Destroy();
}