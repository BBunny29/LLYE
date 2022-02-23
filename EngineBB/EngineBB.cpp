#include "pch.h"
#include "EngineBB.h"

#include "DLLImporter.h"
#include "Timer.h"
#include "KeyboardClass.h"
#include "MouseClass.h"

static HMODULE g_hExecutiveHandle;
typedef HRESULT(*CREATE_INSTANCE_FUNC)(void** ppv);

EngineBB::EngineBB()
	: m_spDLLImporter(nullptr)
{
}

EngineBB::~EngineBB()
{
}

HRESULT EngineBB::Init()
{
	m_spDLLImporter = std::make_shared<DLLImporter>();
	m_spDX11Renderer = m_spDLLImporter->CreateRenderer(L"");

	return S_OK;
}

int EngineBB::testFunc(int i)
{
	return i + 1;
}

//std::shared_ptr<IRenderer> EngineBB::CreateRenderer(const wchar_t* dllPath)
//{
//	IRenderer* pExecutive;
//	HRESULT hr;
//
//#ifdef _DEBUG
//	g_hExecutiveHandle = ::LoadLibrary(L"../OwnLibs/Libs/DX11_x64Debug.dll");
//#else
//	g_hExecutiveHandle = ::LoadLibrary(L"DX11_x64Release.dll");
//#endif
//
//	if (g_hExecutiveHandle == 0)
//	{
//		return nullptr;
//	}
//
//	CREATE_INSTANCE_FUNC pFunc;
//	pFunc = (CREATE_INSTANCE_FUNC)::GetProcAddress(g_hExecutiveHandle, "DllCreateInstance");
//
//	hr = pFunc((void**)&pExecutive);
//	if (hr != S_OK)
//	{
//		MessageBox(NULL, L"CreateExecutive() - Executive 생성 실패", L"Error", MB_OK);
//		return FALSE;
//	}
//
//	std::shared_ptr<IRenderer> _newPtr(pExecutive);
//
//	return _newPtr;
//}
