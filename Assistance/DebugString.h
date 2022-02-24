#pragma once
#include "pch.h"

#include <malloc.h>
#include <stdarg.h>
#include <stdio.h>
#include <debugapi.h>

#define PDS(x, ...) PrintDebugString(x, ##__VA_ARGS__)
#define PDS_LOG PrintDebugString("File : %s ", __FILE__); PrintDebugString("Func : %s ", __FUNCTION__); 

inline void PrintDebugString(char const* const format, ...)
{
	va_list args;
	int     len;
	char* buffer;

	// retrieve the variable arguments
	va_start(args, format);

	len = _vscprintf(format, args) // _vscprintf doesn't count
		+ 1; // terminating '\0'

	buffer = (char*)malloc(len * sizeof(char));

	if (0 != buffer)
	{
		vsprintf_s(buffer, len, format, args); // C4996
		// Note: vsprintf is deprecated; consider using vsprintf_s instead
		puts(buffer);

		OutputDebugStringA(buffer);
		OutputDebugStringA("\n");

		free(buffer);
	}
	va_end(args);
}