#pragma once
#include "pch.h"

#include "GameProcess.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:

/// <summary>
/// 루루팡 여의주의 시작점 Main
/// 
/// 2022. 02. 19 B.BUNNY
/// </summary>
/// <param name="hInstance"></param>
/// <param name="hPrevInstance"></param>
/// <param name="lpCmdLine"></param>
/// <param name="nCmdShow"></param>
/// <returns></returns>
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// 게임 진행 클래스
	// 내부에서 윈도 생성과 메시지 콜백을 처리한다.
	// 또한 그래픽스 엔진 등을 포함한다.
	GameProcess* _pGameProcess = new GameProcess();
	_pGameProcess->Initialize(hInstance, "LLYE2", "MyWindowClass", 1920, 1080);
	while (_pGameProcess->ProcessMessages() == true)
	{
		_pGameProcess->Update();
		_pGameProcess->Draw();
	}
	_pGameProcess->Finalize();

	return 0;
}

