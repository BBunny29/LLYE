#pragma once
#include <memory>

__interface IEngineBB
{
public:
	virtual HRESULT Init() abstract;
	virtual int testFunc(int i) abstract;

	//virtual std::shared_ptr<IRenderer> CreateRenderer(const wchar_t* dllPath) abstract;
};