#pragma once
#include "pch.h"

#include "GameProcess.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE p_hInst;                                // 현재 인스턴스입니다.
WCHAR p_szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR p_szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

/// <summary>
/// 루루팡 여의주의 시작점 Main
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

