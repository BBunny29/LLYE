#pragma once

/// 키보드 이벤트 타입
enum class eKeyboardEvnet
{
	Down,		// 처음 눌렸을 때
	Press,		// 누르는 중일 때
	Up,			// 처음 뗐을 때
	Release,	// 완전히 떼진 상태
	Invalid		// 오류
};

/// 마우스 이벤트 타입
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