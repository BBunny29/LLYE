#pragma once
#include "pch.h"

/// <summary>
/// DLL로더
/// </summary>
static HMODULE g_hExecutiveHandle;
typedef HRESULT(*CREATE_INSTANCE_FUNC)(void** ppv);
namespace DllLoader
{
	template <typename T>
	std::shared_ptr<T> LoadDll(const wchar_t* dllPath)
	{
		T* pExecutive;
		HRESULT hr;

		g_hExecutiveHandle = ::LoadLibrary(dllPath);

		if (g_hExecutiveHandle == 0)
		{
			return nullptr;
		}

		CREATE_INSTANCE_FUNC pFunc;
		pFunc = (CREATE_INSTANCE_FUNC)::GetProcAddress(g_hExecutiveHandle, "DllCreateInstance");

		hr = pFunc((void**)&pExecutive);
		if (hr != S_OK)
		{
			MessageBox(NULL, L"CreateExecutive() - Executive 생성 실패", L"Error", MB_OK);
			return FALSE;
		}

		std::shared_ptr<T> _newPtr(pExecutive);

		return _newPtr;
	}
}
