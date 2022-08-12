#include "pch.h"
#include "ErrorLogger.h"

#include "COMException.h"
#include "StringHelper.h"
#include <comdef.h>

void ErrorLogger::Log(std::string message, ErrorKind eERRORKIND)
{
	std::string error_type;
	std::string error_message;

	switch (eERRORKIND)
	{
	case ErrorKind::eDEFAULT:
		error_type = "Error";
		break;
	case ErrorKind::ePath:
		error_type = "Path Error";
		break;
	}

	error_message = error_type + " : \n" + message;
	MessageBoxA(NULL, error_message.c_str(), error_type.c_str(), MB_ICONERROR);
}

void ErrorLogger::Log(HRESULT hr, std::string message)
{
	_com_error error(hr);
	std::wstring error_message = L"Error: " + StringHelper::StringToWString(message) + L"\n" + error.ErrorMessage();
	MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR);
}

void ErrorLogger::Log(HRESULT hr, std::wstring message)
{
	_com_error error(hr);
	std::wstring error_message = L"Error: " + message + L"\n" + error.ErrorMessage();
	MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR);
}

void ErrorLogger::Log(COMException& exception)
{
	std::wstring error_message = exception.what();
	MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR);
}
