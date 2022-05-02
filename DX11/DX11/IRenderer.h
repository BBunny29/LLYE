#pragma once

/// 가장 기초가 되는 클래스로 렌더러의 인터페이스다.
/// 용책에서 이 엔진을 상속하는 구조로 다양한 렌더러를 작성한다.
/// 여기서 직접 Initialize를 하지만, 이제 해당 작업은 렌더러에게 맡긴다.

/// 210629
/// 필요없는 인터페이스를 제거해야 한다.
/// 생각을 해보니 OpenGL 등을 쓰지는 않겠지만, ID3D12를 사용할 여지는 있을 것 같다.
class IRenderer abstract
{
public:
	IRenderer() {};
	virtual ~IRenderer() {};			// 소멸자를 virtual로 하지 않은 경우, 자식 소멸자가 호출되지 않는다.

public:
	// 엔진 초기화 함수
	virtual bool Initialize(int hinst, int hWnd, int screenWidth, int screenHeight) abstract;

	// 업데이트
	virtual void Update(float deltaTIme) abstract;

	// 렌더 시작 부분을 묶는다.
	virtual void BeginRender() abstract;

	// 렌더링의 끝 부분으로 제출(Present) 작업이 이루어진다.
	virtual void EndRender() abstract;

	// 엔진을 종료한다.
	virtual void Finalize() abstract;

public:
	virtual void Render() abstract;
};
