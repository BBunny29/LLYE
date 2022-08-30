#include "pch.h"
#include "Input.h"

#include "Keyboard.h"
#include "Mouse.h"

Input::Input()
{
}

Input::~Input()
{
}

bool Input::Initialize()
{
	m_spKeyboard = std::make_shared<Keyboard>();
	m_spMouse = std::make_shared<Mouse>();

	return true;
}

void Input::Finalize()
{
}

void Input::Update()
{
	m_spKeyboard->UpdateKeyboardState();
	m_spMouse->UpdateMouse();
}

void Input::SetKeyboardState(eInput upDown, unsigned char keycode)
{
	switch (upDown)
	{
		case eInput::Down :
		{
			m_spKeyboard->OnKeyDown(keycode);
			break;
		}
		case eInput::Up :
		{
			m_spKeyboard->OnKeyUp(keycode);
			break;
		}
	}
}

void Input::SetMousePos(POINT mousePos)
{
	m_spMouse->m_mousePos = mousePos;
}

void Input::SetMouseRowPos(POINT mouseRowPos)
{
	m_spMouse->m_mouseRowPos = mouseRowPos;
}

void Input::SetMouseState(eInput upDown, eMouseButtonType buttonType, POINT clickPoint)
{
	switch (upDown)
	{
		case eInput::Down:
		{
			m_spMouse->OnButtonDown(buttonType, clickPoint);
			break;
		}
		case eInput::Up:
		{
			m_spMouse->OnButtonUp(buttonType, clickPoint);
			break;
		}
	}

}

void Input::SetMouseWheelState(eInput upDown, POINT clickPoint)
{
	switch (upDown)
	{
		case eInput::Down:
		{
			m_spMouse->OnWheelDown(clickPoint);
			break;
		}
		case eInput::Up:
		{
			m_spMouse->OnWheelUp(clickPoint);
			break;
		}
	}


}

bool Input::IsKeyDown(unsigned char keycode)
{
	return m_spKeyboard->IsKeyDown(keycode);
}

bool Input::IsKeyPress(unsigned char keycode)
{
	return m_spKeyboard->IsKeyPress(keycode);
}

bool Input::IsKeyUp(unsigned char keycode)
{
	return m_spKeyboard->IsKeyUp(keycode);
}

bool Input::IsKeyRelease(unsigned char keycode)
{
	return m_spKeyboard->IsKeyRelease(keycode);
}



bool Input::IsDown(eMouseButtonType mouseType)
{
	return m_spMouse->IsButtonDown(mouseType);
}

bool Input::IsPress(eMouseButtonType mouseType)
{
	return m_spMouse->IsButtonPress(mouseType);
}

bool Input::IsUp(eMouseButtonType mouseType)
{
	return m_spMouse->IsButtonUp(mouseType);
}

bool Input::IsRelease(eMouseButtonType mouseType)
{
	return m_spMouse->IsButtonRelease(mouseType);
}

bool Input::IsWheelUp()
{
	return m_spMouse->m_iswheelUp;
}

bool Input::IsWheelDown()
{
	return m_spMouse->m_iswheelDown;
}



POINT Input::GetMousePos()
{
	return m_spMouse->m_mousePos;
}

POINT Input::GetMouseRowPos()
{
	return m_spMouse->m_mouseRowPos;
}

POINT Input::GetClickDownPos()
{
	return m_spMouse->m_clickDownPos; 
}

POINT Input::GetClickUpPos()
{
	return m_spMouse->m_clickUpPos; ;
}

