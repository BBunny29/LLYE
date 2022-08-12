#pragma once
#include "pch.h"

#include <malloc.h>
#include <stdarg.h>
#include <stdio.h>
#include <debugapi.h>

namespace DebugString
{
	// Print함수 재정의
	#define PDS(x, ...) Print(x, ##__VA_ARGS__)
	// Print함수로 로그 출력
	#define PDS_LOG Print("File : %s    Func : %s    Line : %d", __FILE__, __FUNCTION__, __LINE__)

	/// <summary>
	/// 디버깅용 문자 출력(가변인자 사용) 
	/// 출력창에 문자를 찍을수 있다.
	/// 
	/// 2022.08.11 B.Bunny
	/// </summary>
	inline void Print(char const* const format, ...)
	{
#ifdef _DEBUG
		// 가변인수들을 저장하는 스택 주소 포인터 
		va_list _args;
		int _len;
		char* _buffer;

		// args가 첫번째 가변인수를 가리킬 수 있도록 초기화
		va_start(_args, format);

		_len = _vscprintf(format, _args) + 1; // _vscprintf는 널문자('\0')를 세지않으므로 +1 해준다.

		_buffer = (char*)malloc(_len * sizeof(char));

		if (0 != _buffer)
		{
			vsprintf_s(_buffer, _len, format, _args);

			OutputDebugStringA(_buffer);
			OutputDebugStringA("\n");

			free(_buffer);
		}
		va_end(_args);
#endif
	}
}
