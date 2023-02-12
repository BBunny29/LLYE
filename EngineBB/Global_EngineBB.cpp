#include "pch.h"
#include "Global_EngineBB.h"

#include "EngineBBDllDefine.h"
#include "Interface_EngineBB.h"
#include "EngineBB.h"
#include "Input.h"

/// 1. ������Ʈ�� ���ο��� ����ϱ� ���� �������� ������ �������ִ´�. 
static IEngineBB* g_Engine = nullptr;

/// �������̽��� ���������� "DllCreateInstance" + "�������̽� �̸�" ���� ���� ��
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