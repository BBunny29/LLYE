#include "pch.h"
#include "EngineBB.h"

#include "DllLoader.h"

#include "Timer.h"
#include "KeyboardClass.h"
#include "MouseClass.h"

EngineBB::EngineBB()
{
}

EngineBB::~EngineBB()
{
}

HRESULT EngineBB::Init()
{
	#ifdef _WIN64
	#ifdef _DEBUG
		m_spDX11Renderer = DllLoader::LoadDll<IRenderer>(L"../../OwnLibs/Libs/DX11_x64Debug.dll");
	#else
		m_spDX11Renderer = DllLoader::LoadDll<IRenderer>(L"DX11_x64Release.dll");
	#endif
	#else
	#ifdef _DEBUG
		m_spDX11Renderer = DllLoader::LoadDll<IRenderer>(L"../../OwnLibs/Libs/DX11_x86Debug.dll");
	#else
		m_spDX11Renderer = DllLoader::LoadDll<IRenderer>(L"DX11_x86Release.dll");
	#endif
	#endif

	return S_OK;
}

int EngineBB::testFunc(int i)
{
	return i + 1;
}
