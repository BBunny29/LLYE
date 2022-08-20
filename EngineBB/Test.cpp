#include "pch.h"
#include "Test.h"
#include "IRenderer.h"

#include "DllLoader.h"

#include "Timer.h"
//#include "KeyboardClass.h"
//#include "MouseClass.h"

Test::Test()
{
}

Test::~Test()
{
}

HRESULT Test::Initialize(int hWND, int width, int height)
{
//#ifdef _WIN64
//#ifdef _DEBUG
//	DllLoader::LoadDll<IRenderer>(L"../../OwnLibs/Libs/DX11_x64Debug.dll", m_spDX11Renderer);
//#else
//	m_spDX11Renderer = DllLoader::LoadDll<IRenderer>(L"DX11_x64Release.dll");
//#endif
//#else
//#ifdef _DEBUG
//	m_spDX11Renderer = DllLoader::LoadDll<IRenderer>(L"../../OwnLibs/Libs/DX11_x86Debug.dll");
//#else
//	m_spDX11Renderer = DllLoader::LoadDll<IRenderer>(L"DX11_x86Release.dll");
//#endif
//#endif
//
//	m_spDX11Renderer->Initialize(hWND, width, height);

	return S_OK;
}
