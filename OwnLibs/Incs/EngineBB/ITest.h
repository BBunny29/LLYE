#pragma once
#include <memory>

__interface ITest
{
public:
	virtual HRESULT Initialize(int hWND, int width, int height) abstract;

};