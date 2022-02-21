#include "pch.h"
#include "EngineBB.h"

#include "Timer.h"
#include "KeyboardClass.h"
#include "MouseClass.h"

static HMODULE g_hExecutiveHandle;
typedef HRESULT(*CREATE_INSTANCE_FUNC)(void** ppv);

EngineBB::EngineBB()
{
}

EngineBB::~EngineBB()
{
}

HRESULT EngineBB::Init()
{
	m_pRenderer = CreateRenderer();

	return S_OK;
}

std::shared_ptr<IRenderer> EngineBB::CreateRenderer()
{
	IRenderer* pExecutive;
	HRESULT hr;

#ifdef _DEBUG
	g_hExecutiveHandle = ::LoadLibrary(L"../OwnLibs/Libs/DX11_x64Debug.dll");
#else
	g_hExecutiveHandle = ::LoadLibrary(L"DX11_x64Release.dll");
#endif

	CREATE_INSTANCE_FUNC pFunc;
	pFunc = (CREATE_INSTANCE_FUNC)::GetProcAddress(g_hExecutiveHandle, "DllCreateInstance");

	hr = pFunc((void**)&pExecutive);
	if (hr != S_OK)
	{
		MessageBox(NULL, L"CreateExecutive() - Executive 생성 실패", L"Error", MB_OK);
		return FALSE;
	}

	std::shared_ptr<IRenderer> _newPtr(pExecutive);

	return _newPtr;
}
