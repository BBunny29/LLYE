#pragma once
#include <memory>
__interface IRenderer;

class DLLImporter2
{
public:
	DLLImporter2();
	~DLLImporter2();

	//���ø����� �����Ҽ� ���� ������??
	std::shared_ptr<IRenderer> CreateRenderer(const wchar_t* dllPath);
private:

};

