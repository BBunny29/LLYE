#pragma once
#include "pch.h"

#include <malloc.h>
#include <stdarg.h>
#include <stdio.h>
#include <debugapi.h>

namespace DebugString
{
	// Print�Լ� ������
	#define PDS(x, ...) Print(x, ##__VA_ARGS__)
	// Print�Լ��� �α� ���
	#define PDS_LOG Print("File : %s    Func : %s    Line : %d", __FILE__, __FUNCTION__, __LINE__)

	/// <summary>
	/// ������ ���� ���(�������� ���) 
	/// ���â�� ���ڸ� ������ �ִ�.
	/// 
	/// 2022.08.11 B.Bunny
	/// </summary>
	inline void Print(char const* const format, ...)
	{
#ifdef _DEBUG
		// �����μ����� �����ϴ� ���� �ּ� ������ 
		va_list _args;
		int _len;
		char* _buffer;

		// args�� ù��° �����μ��� ����ų �� �ֵ��� �ʱ�ȭ
		va_start(_args, format);

		_len = _vscprintf(format, _args) + 1; // _vscprintf�� �ι���('\0')�� ���������Ƿ� +1 ���ش�.

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
