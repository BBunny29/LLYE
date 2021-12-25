#pragma once
#include "LibraryDefine.h"

class Timer;

class EngineBB
{
public:
	EngineBB();
	~EngineBB();

private:
	Timer* m_timer;
	KeyboardClass* m_keyboard;
	MouseClass* m_mouse;

};