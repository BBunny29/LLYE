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


private:
	std::shared_ptr<IRenderer> CreateRenderer();

private:

	std::shared_ptr<IRenderer> m_pRenderer;

	Timer* m_timer;
	KeyboardClass* m_keyboard;
	MouseClass* m_mouse;

};