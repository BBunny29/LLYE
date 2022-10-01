#include "pch.h"
#include "Interface_ResourceManager.h"
#include "DX11ResourceManager.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

/// 인터페이스를 내보내려면 "DllCreateInstance" + "인터페이스 이름" 으로 지을것

extern "C" _RESORCE_DLL HRESULT DllCreateInstanceIResourceManager(void** ppv)
{
    HRESULT hr;
    IResourceManager* pExecutive = new DX11ResourceManager;
    if (!pExecutive)
    {
        hr = E_OUTOFMEMORY;
        return hr;
    }
    
    hr = S_OK;
    *ppv = pExecutive;

    return hr;
}