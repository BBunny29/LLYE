#pragma once
#include "Enum_EngineBB.h"
/// 외부 프로젝트와 연결될 EngineBB의 인터페이스들만 모아놓은 .h

/// <summary>
/// 엔진의 인터페이스(껍데기)
/// 바깥부분(게임 프로젝트)에서 사용할 함수들만 가상함수로 만든다.
/// 
/// 2022.08.21 B.Bunny
/// </summary>
__interface IEngineBB
{
public:
	virtual bool Initialize(int hWND, int width, int height) abstract;
	virtual bool Loop() abstract;
	virtual void Finalize() abstract;

	/// Input(keyboard / mouse) 연결
	virtual void SetInput(std::shared_ptr<__interface IInput>& _input) abstract;
	virtual std::shared_ptr<__interface IInput> GetInput() abstract;

	virtual LRESULT ImGuiHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) abstract;
};

__interface IInput
{
public:
	/// 키보드

	/// 마우스
};