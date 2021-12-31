#pragma once
#include "LibraryDefine.h"

class Timer;
class KeyboardClass;
class MouseClass;

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