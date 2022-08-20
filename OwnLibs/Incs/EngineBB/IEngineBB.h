#pragma once
#include <memory>

__interface IEngineBB
{
public:
	virtual bool Initialize(int hWND, int width, int height) abstract;
	virtual void Finalize() abstract;
};