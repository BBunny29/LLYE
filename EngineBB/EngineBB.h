#pragma once
#include "EngineBBLibraryDefine.h"
#include "EngineBBDefine.h"
#include "IEngineBB.h"

class Timer;
class KeyboardClass;
class MouseClass;

class EngineBB : public IEngineBB
{
public:
	EngineBB();
	~EngineBB();

private:
	Timer* m_timer;
	KeyboardClass* m_keyboard;
	MouseClass* m_mouse;

};