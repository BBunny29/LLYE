#pragma once
#include <memory>
__interface IRenderer;

class DLLImporter2
{
public:
	DLLImporter2();
	~DLLImporter2();

	//템플릿으로 구현할수 있지 않을까??
	std::shared_ptr<IRenderer> CreateRenderer(const wchar_t* dllPath);
private:

};

