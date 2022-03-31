#pragma once
#include "EngineBBLibraryDefine.h"
#include "EngineBBDefine.h"
#include "IEngineBB.h"

/// <summary>
/// 필요한것 : 
/// 1. 타이머
/// 2. 컴포넌트 시스템
/// 3. 마우스, 키보드
/// 4. 커밋테스트
/// </summary>

__interface IRenderer;

class EngineBB : public IEngineBB
{
public:
	EngineBB();
	~EngineBB();

	virtual HRESULT Init(int hWND, int width, int height) override;
	
private:
	std::shared_ptr<IRenderer> m_spDX11Renderer;

	//Timer* m_timer;
	//KeyboardClass* m_keyboard;
	//MouseClass* m_mouse;

};