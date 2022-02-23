#include "pch.h"
#include "DLLImporter.h"

static HMODULE g_hExecutiveHandle;
typedef HRESULT(*CREATE_INSTANCE_FUNC)(void** ppv);

//template <typename T>
//std::shared_ptr<T> DLLImporter::CreateDLL(const wchar_t* dllPath)
//{
//	IEngineBB* pExecutive;
//	HRESULT hr;
//
//#ifdef _DEBUG
//	g_hExecutiveHandle = ::LoadLibrary(L"../../OwnLibs/Libs/DX11_x64Debug.dll");
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
//	std::shared_ptr<IEngineBB> _newPtr(pExecutive);
//
//	return _newPtr;
//}
