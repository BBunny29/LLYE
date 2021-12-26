#pragma once
#include "IRenderer.h"

class DX11Renderer : public IRenderer
{
public:
	DX11Renderer();
	~DX11Renderer();

	bool Initialize(int hinst, int hWnd, int screenWidth, int screenHeight);

	void Update(float deltaTIme);
	void BeginRender();
	void EndRender();
	void Finalize();

public:
	void Render();

private:

};
