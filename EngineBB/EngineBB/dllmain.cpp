// dllmain.cpp : DLL ���ø����̼��� �������� �����մϴ�.

// ������ �Լ��� ȣ��Ǵ� ������ ������ �����ϱ� ���� ������ ������,
// DLL�� ���μ����� �Ǵ� �����庰�� �ʱ�ȭ�� �����ϰų� ������ �������� ȣ��Ǳ⵵ �Ѵ�.
#include "pch.h"
#include "IEngineBB.h"
#include "EngineBB.h"

BOOL APIENTRY DllMain(HMODULE hModule,            
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved)
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

extern "C" _EBB_DLL HRESULT DllCreateInstance(void** ppv)
{
    HRESULT hr;
    IEngineBB* pExecutive = new EngineBB;
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
