#pragma once
#include <memory>

__interface IRenderer;

__interface IEngineBB
{
public:
	virtual HRESULT Init(int hWND, int width, int height) abstract;

};