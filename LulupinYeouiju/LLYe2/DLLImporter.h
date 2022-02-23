#pragma once
#include <memory>

//__interface IEngineBB;

static HMODULE g_hExecutiveHandle;
typedef HRESULT(*CREATE_INSTANCE_FUNC)(void** ppv);


class DLLImporter
{
public:
	DLLImporter();
	~DLLImporter();

	//템플릿으로 구현할수 있지 않을까??
	//template <typename T>
	std::shared_ptr<int> CreateDLL(const wchar_t* dllPath)
	{
		int* pExecutive;
		HRESULT hr;

#ifdef _DEBUG
		g_hExecutiveHandle = ::LoadLibrary(L"../../OwnLibs/Libs/EngineBB_x64Debug.dll");
#else
		g_hExecutiveHandle = ::LoadLibrary(L"DX11_x64Release.dll");
#endif

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

		std::shared_ptr<int> _newPtr(pExecutive);

		return _newPtr;
	}

private:
};

