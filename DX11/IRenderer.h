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
	virtual bool Initialize(int hWnd, int screenWidth, int screenHeight) abstract;
	virtual void Finalize() abstract;

	// 렌더 시작 부분을 묶는다.
	virtual void BeginRender() abstract;
	// 렌더링의 끝 부분으로 제출(Present) 작업이 이루어진다.
	virtual void EndRender() abstract;
	virtual void Render() abstract;

	virtual void OnResize(int width, int height) abstract;

	/// Getter
	virtual HRESULT GetDeviceAndDeviceContext(void** device, void** deviceContext) abstract;

};