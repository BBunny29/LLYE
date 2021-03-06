#pragma once
#include "pch.h"

#include <malloc.h>
#include <stdarg.h>
#include <stdio.h>
#include <debugapi.h>

/// <summary>
/// 가변인자를 사용해서 디버깅용 문자 출력
/// </summary>

namespace DebugString
{

#define PDS(x, ...) Print(x, ##__VA_ARGS__)
#define PDS_LOG Print("File : %s ", __FILE__); PrintDebugString("Func : %s ", __FUNCTION__); 


	inline void Print(char const* const format, ...)
	{
#ifdef _DEBUG
		// 가변인수들을 저장하는 스택 주소 포인터 
		va_list args;
		int     len;
		char* buffer;

		// args가 첫번째 가변인수를 가리킬 수 있도록 초기화
		va_start(args, format);

		len = _vscprintf(format, args) + 1; // _vscprintf는 널문자('\0')를 세지않으므로 +1 해준다.

		buffer = (char*)malloc(len * sizeof(char));

		if (0 != buffer)
		{
			vsprintf_s(buffer, len, format, args);
			
			// 콘솔
			//puts(buffer);

			OutputDebugStringA(buffer);
			OutputDebugStringA("\n");

			free(buffer);
		}
		va_end(args);
#endif
	}

	template<typename T>
	inline void Print(char const* const format, ...)
	{
#ifdef _DEBUG
		// 가변인수들을 저장하는 스택 주소 포인터 
		va_list args;
		int     len;
		char* buffer;

		// args가 첫번째 가변인수를 가리킬 수 있도록 초기화
		va_start(args, format);

		len = _vscprintf(format, args) + 1; // _vscprintf는 널문자를 doesn't count '\0'. terminating '\0'

		buffer = (char*)malloc(len * sizeof(char));

		if (0 != buffer)
		{
			vsprintf_s(buffer, len, format, args);
			
			// 콘솔
			//puts(buffer);

			OutputDebugStringA(buffer);
			OutputDebugStringA("\n");

			free(buffer);
		}
		va_end(args);
#endif
	}

}
