#pragma once
#include "EngineBBLibraryDefine.h"
#include "EngineBBDefine.h"
#include "IEngineBB.h"

/// <summary>
/// 필요한것 : 
/// 1. 컴포넌트 시스템
/// 2. 타이머
/// 3. 마우스, 키보드
/// 4. 
/// </summary>

__interface IRenderer;

class EngineBB : public IEngineBB
{
public:
	EngineBB();
	~EngineBB();

	virtual HRESULT Initialize(int hWND, int width, int height) override;
	
private:
	std::shared_ptr<IRenderer> m_spDX11Renderer;

	//Timer* m_timer;
	//KeyboardClass* m_keyboard;
	//MouseClass* m_mouse;

};