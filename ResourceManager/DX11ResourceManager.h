#pragma once
#include "Interface_ResourceManager.h"


class DX11ResourceManager : public IResourceManager
{
public:
	DX11ResourceManager();
	~DX11ResourceManager();

public:
	virtual bool Initialize() override;

	virtual int GetInfo() override;
};

