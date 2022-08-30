// dllmain.cpp : DLL ���ø����̼��� �������� �����մϴ�.

// ������ �Լ��� ȣ��Ǵ� ������ ������ �����ϱ� ���� ������ ������,
// DLL�� ���μ����� �Ǵ� �����庰�� �ʱ�ȭ�� �����ϰų� ������ �������� ȣ��Ǳ⵵ �Ѵ�.
#include "pch.h"
#include "EngineBBDllDefine.h"
#include "Interface_EngineBB.h"
#include "EngineBB.h"
#include "Input.h"

BOOL APIENTRY DllMain(  HMODULE hModule,
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

/// �������̽��� ���������� "DllCreateInstance" + "�������̽� �̸�" ���� ������

extern "C" _EBB_DLL HRESULT DllCreateInstanceIEngineBB(void** ppv)
{
    HRESULT hr;
    IEngineBB* pExecutive = new EngineBB;

    if (!pExecutive)
    {
        hr = E_OUTOFMEMORY;
        return hr;
    }
    
    hr = S_OK;
    *ppv = pExecutive;
    
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