#pragma once

/// <summary>
/// 렌더러의 인터페이스(껍데기)
/// 바깥부분(엔진)에서 사용할 함수들만 가상함수로 만든다.
/// 
/// 2022.08.21 B.Bunny
/// </summary>
__interface IRenderer
{
public:
	// 렌더러 초기화 함수
	virtual bool Initialize(int hWnd, int screenWidth, int screenHeight) abstract;

	// 렌더 시작 부분을 묶는다.
	virtual void BeginRender() abstract;

	virtual void Render() abstract;

	// 렌더링의 끝 부분으로 제출(Present) 작업이 이루어진다.
	virtual void EndRender() abstract;

	// 엔진을 종료한다.
	virtual void Finalize() abstract;

};