#include "pch.h"
#include "Global_EngineBB.h"

#include "EngineBBDllDefine.h"
#include "Interface_EngineBB.h"
#include "EngineBB.h"
#include "Input.h"

/// 1. 컴포넌트들 내부에서 사용하기 위해 전역으로 엔진을 가지고있는다. 
static IEngineBB* g_Engine = nullptr;

/// 인터페이스를 내보내려면 "DllCreateInstance" + "인터페이스 이름" 으로 지을 것
extern "C" _EBB_DLL HRESULT DllCreateInstanceIEngineBB(void** ppv)
{
    HRESULT hr;
    g_Engine = new EngineBB;

    if (!g_Engine)
    {
        hr = E_OUTOFMEMORY;
        return hr;
    }

    hr = S_OK;
    *ppv = g_Engine;

    return hr;
}

extern "C" _EBB_DLL HRESULT DllCreateInstanceIInput(void** ppv)
{
    HRESULT hr;
    IInput* pExecutive = new Input;

    if (!pExecutive)
    {
        hr = E_OUTOFMEMORY;
        return hr;
    }

    hr = S_OK;
    *ppv = pExecutive;

    return hr;
}




_EBB_DLL int WINDOW::GetScreenWidth()
{
    ASSERT_NULLCHECK(g_Engine, "EngineBB is null");

    if (g_Engine != nullptr)
    {
        return g_Engine->GetScreenWidth();
    }
    return 0;
}

_EBB_DLL int WINDOW::GetScreenHeight()
{
    ASSERT_NULLCHECK(g_Engine, "EngineBB is null");

    if (g_Engine != nullptr)
    {
        return g_Engine->GetScreenHeight();
    }
    return 0;
}

_EBB_DLL HWND WINDOW::GetHWND()
{
    ASSERT_NULLCHECK(g_Engine, "EngineBB is null");

    if (g_Engine != nullptr)
    {
        return g_Engine->GetHWND();
    }
    return 0;
}