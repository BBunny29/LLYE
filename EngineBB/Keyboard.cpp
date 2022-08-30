#include "pch.h"
#include "Keyboard.h"

Keyboard::Keyboard()
{
	for (int i = 0; i < 256; i++)
		this->keyStates[i] = false;

	for (int i = 0; i < 256; i++)
		this->keyStatesBefore[i] = false;
}

Keyboard::~Keyboard()
{

}

void Keyboard::UpdateKeyboardState()
{
	for (int i = 0; i < 256; i++)
		keyStatesBefore[i] = keyStates[i];
}

void Keyboard::OnKeyDown(const unsigned char keycode)
{
	this->keyStates[keycode] = true;
}

void Keyboard::OnKeyUp(const unsigned char keycode)
{
	this->keyStates[keycode] = false;
}

bool Keyboard::IsKeyDown(const unsigned char keycode)
{
	if (keyStatesBefore[keycode] == false && keyStates[keycode] == true)
	{
		return true;
	}
	return false;
}

bool Keyboard::IsKeyPress(const unsigned char keycode)
{
	return keyStates[keycode];
}

bool Keyboard::IsKeyUp(const unsigned char keycode)
{
	if (keyStates[keycode] == false && keyStatesBefore[keycode] == true)
	{
		return true;
	}
	return false;
}

bool Keyboard::IsKeyRelease(const unsigned char keycode)
{
	return !keyStates[keycode];
}

