#pragma once

/// Ű���� �̺�Ʈ Ÿ��
enum class eKeyboardEvnet
{
	Down,		// ó�� ������ ��
	Press,		// ������ ���� ��
	Up,			// ó�� ���� ��
	Release,	// ������ ���� ����
	Invalid		// ����
};

/// ���콺 �̺�Ʈ Ÿ��
enum class eMouseEvent
{
	LDown,
	LPress,
	LUp,
	LRelease,

	RDown,
	RPress,
	RUp,
	RRelease,
	
	MDown,
	MPress,
	MUp,
	MRelease,
	
	WheelUp,
	WheelDown,
	
	Move,
	RAW_MOVE,
	Invalid
};