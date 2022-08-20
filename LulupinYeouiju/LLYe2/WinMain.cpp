#pragma once
#include "pch.h"

#include "GameProcess.h"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE p_hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR p_szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR p_szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

/// <summary>
/// ����� �������� ������ Main
/// 
/// 2022. 02. 19 B.BUNNY
/// </summary>
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	GameProcess* _pGameProcess = new GameProcess();
	if (!_pGameProcess->Initialize(hInstance, "LLYE2", "MyWindowClass", 1920, 1080))
	{
		return 0;
	}
	
	while (_pGameProcess->ProcessMessages() == true)
	{
		_pGameProcess->Update();
		_pGameProcess->Draw();
	}
	
	_pGameProcess->Finalize();

	return 0;
}

