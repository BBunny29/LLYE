#include "pch.h"
#include "Mouse.h"

Mouse::Mouse()
	: m_mousePos({ 0, 0 })
	, m_mouseRowPos({ 0, 0 })
	, m_clickDownPos({ 0, 0 })
	, m_clickUpPos({ 0, 0 })
	, m_iswheelUp(false)
	, m_iswheelDown(false)
{
	for (int i = 0; i < static_cast<int>(eMouseButtonType::Count); i++)
		this->buttonStates[i] = false;

	for (int i = 0; i < static_cast<int>(eMouseButtonType::Count); i++)
		this->buttonStatesBefore[i] = false;
}

Mouse::~Mouse()
{
}

void Mouse::UpdateMouse()
{
	for (int i = 0; i < static_cast<int>(eMouseButtonType::Count); i++)
		buttonStatesBefore[i] = buttonStates[i];
	m_iswheelUp = false;
	m_iswheelDown = false;
}

void Mouse::OnMouseMove(POINT mousePos)
{
	m_mousePos = mousePos;
}

void Mouse::OnMouseMoveRaw(POINT mouseRowPos)
{
	m_mouseRowPos = mouseRowPos;
}

void Mouse::OnButtonDown(eMouseButtonType buttonType, POINT clickPoint)
{
	buttonStates[static_cast<int>(buttonType)] = true;
	m_clickDownPos = clickPoint;
}

void Mouse::OnButtonUp(eMouseButtonType buttonType, POINT clickPoint)
{
	buttonStates[static_cast<int>(buttonType)] = false;
	m_clickUpPos = clickPoint;
}




void Mouse::OnWheelUp(POINT mousePos)
{
	m_iswheelUp = true;
}

void Mouse::OnWheelDown(POINT mousePos)
{
	m_iswheelDown = true;
}





bool Mouse::IsButtonDown(eMouseButtonType buttonType)
{
	if (buttonStatesBefore[static_cast<int>(buttonType)] == false && buttonStates[static_cast<int>(buttonType)] == true)
	{
		return true;
	}
	return false;
}

bool Mouse::IsButtonPress(eMouseButtonType buttonType)
{
	return  buttonStates[static_cast<int>(buttonType)];
}

bool Mouse::IsButtonUp(eMouseButtonType buttonType)
{
	if (buttonStates[static_cast<int>(buttonType)] == false && buttonStatesBefore[static_cast<int>(buttonType)] == true)
	{
		return true;
	}
	return false;
}

bool Mouse::IsButtonRelease(eMouseButtonType buttonType)
{
	return !buttonStates[static_cast<int>(buttonType)];
}

