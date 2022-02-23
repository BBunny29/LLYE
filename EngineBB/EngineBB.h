#pragma once
#include "EngineBBLibraryDefine.h"
#include "EngineBBDefine.h"
#include "IEngineBB.h"

__interface IRenderer;

class EngineBB : public IEngineBB
{
public:
	EngineBB();
	~EngineBB();

	virtual HRESULT Init() override;

	virtual int testFunc(int i) override;


private:
	std::shared_ptr<IRenderer> m_spDX11Renderer;

	//Timer* m_timer;
	//KeyboardClass* m_keyboard;
	//MouseClass* m_mouse;

};