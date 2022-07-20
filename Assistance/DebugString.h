#pragma once
#include "pch.h"

#include <malloc.h>
#include <stdarg.h>
#include <stdio.h>
#include <debugapi.h>

/// <summary>
/// �������ڸ� ����ؼ� ������ ���� ���
/// </summary>

namespace DebugString
{

#define PDS(x, ...) Print(x, ##__VA_ARGS__)
#define PDS_LOG Print("File : %s ", __FILE__); PrintDebugString("Func : %s ", __FUNCTION__); 


	inline void Print(char const* const format, ...)
	{
#ifdef _DEBUG
		// �����μ����� �����ϴ� ���� �ּ� ������ 
		va_list args;
		int     len;
		char* buffer;

		// args�� ù��° �����μ��� ����ų �� �ֵ��� �ʱ�ȭ
		va_start(args, format);

		len = _vscprintf(format, args) + 1; // _vscprintf�� �ι���('\0')�� ���������Ƿ� +1 ���ش�.

		buffer = (char*)malloc(len * sizeof(char));

		if (0 != buffer)
		{
			vsprintf_s(buffer, len, format, args);
			
			// �ܼ�
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
		// �����μ����� �����ϴ� ���� �ּ� ������ 
		va_list args;
		int     len;
		char* buffer;

		// args�� ù��° �����μ��� ����ų �� �ֵ��� �ʱ�ȭ
		va_start(args, format);

		len = _vscprintf(format, args) + 1; // _vscprintf�� �ι��ڸ� doesn't count '\0'. terminating '\0'

		buffer = (char*)malloc(len * sizeof(char));

		if (0 != buffer)
		{
			vsprintf_s(buffer, len, format, args);
			
			// �ܼ�
			//puts(buffer);

			OutputDebugStringA(buffer);
			OutputDebugStringA("\n");

			free(buffer);
		}
		va_end(args);
#endif
	}

}
