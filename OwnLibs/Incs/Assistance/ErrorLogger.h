#pragma once

#include <Windows.h>
#include <string>

/// error Á¾·ù
enum class ErrorKind
{
	eDEFAULT = 0,
	ePath,
};

/// <summary>
/// Error Logger 
/// 	
/// 2022.08.11 B.Bunny
/// </summary>
class ErrorLogger
{
public:
	static void Log(std::string message, ErrorKind eERRORKIND = ErrorKind::eDEFAULT);
	static void Log(HRESULT hr, std::string message);
	static void Log(HRESULT hr, std::wstring message);
	static void Log(class COMException& exception);
};