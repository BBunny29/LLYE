// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.
#include "pch.h"
#include "DX11DllDefine.h"
#include "IRenderer.h"
#include "DX11Renderer.h"

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

extern "C" _RDX11_DLL HRESULT DllCreateInstance(void** ppv)
{
    HRESULT hr;
    IRenderer* pExecutive = new DX11Renderer;
    if (!pExecutive)
    {
        hr = E_OUTOFMEMORY;
        goto lb_return;
    }
    hr = S_OK;
    *ppv = pExecutive;
lb_return:
    return hr;
}
