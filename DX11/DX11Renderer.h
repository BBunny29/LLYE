#pragma once
#include "DX11LibraryDefine.h"
#include "IRenderer.h"

class DX11Renderer : public IRenderer
{
public:
	DX11Renderer();
	~DX11Renderer();

	virtual bool Initialize(int hinst, int hWnd, int screenWidth, int screenHeight) override;

	virtual void BeginRender() override;
	virtual void EndRender() override;
	virtual void Finalize() override;

public:
	virtual void Render() override;

private:
	int m_test;
};
