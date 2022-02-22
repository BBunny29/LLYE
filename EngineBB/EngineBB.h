#pragma once
#include "EngineBBLibraryDefine.h"
#include "EngineBBDefine.h"
#include "IEngineBB.h"
#include <memory>

__interface IRenderer;

class Timer;
class KeyboardClass;
class MouseClass;

class EngineBB : public IEngineBB
{
public:
	EngineBB();
	~EngineBB();

	HRESULT Init();

	virtual int testFunc(int i) override;

private:
	//virtual std::shared_ptr<IRenderer> CreateRenderer(const wchar_t* dllPath) override;

private:

	std::shared_ptr<IRenderer> m_pRenderer;

	//Timer* m_timer;
	//KeyboardClass* m_keyboard;
	//MouseClass* m_mouse;

};