#include "pch.h"
#include "ErrorLogger.h"

#include <comdef.h>

#include "COMException.h"
#include "StringHelper.h"

void ErrorLogger::Log(const std::string& message)
{
	std::string error_message;

	error_message = "Error : \n" + message;
	MessageBoxA(NULL, error_message.c_str(), "Error", MB_ICONERROR);
}

void ErrorLogger::Log(const std::string& message, const std::string& file, const std::string& function, int line)
{
	std::string error_message;

	error_message = "Error : \n" + message;
	error_message += "\nFile: " + file;
	error_message += "\nFunction: " + function;
	error_message += "\nLine: " + std::to_string(line);
	MessageBoxA(NULL, error_message.c_str(), "Error", MB_ICONERROR);
}

void ErrorLogger::Log_HR(HRESULT hr, const std::string& message)
{
	_com_error error(hr);
	std::wstring error_message = L"Error: " + StringHelper::StringToWString(message) + L"\n" + error.ErrorMessage();
	MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR);
}

void ErrorLogger::Log_HR(HRESULT hr, const std::string& message, const std::string& file, const std::string& function, int line)
{
	_com_error error(hr);
	std::wstring error_message = L"Error: " + StringHelper::StringToWString(message) + L"\n" + error.ErrorMessage();
	error_message += L"\nFile: " + StringHelper::StringToWString(file);
	error_message += L"\nFunction: " + StringHelper::StringToWString(function);
	error_message += L"\nLine: " + StringHelper::StringToWString(std::to_string(line));
	MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR);
}

void ErrorLogger::LogW_HR(HRESULT hr, const std::wstring& message)
{
	_com_error error(hr);
	std::wstring error_message = L"Error: " + message + L"\n" + error.ErrorMessage();
	MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR);
}

void ErrorLogger::LogW_HR(HRESULT hr, const std::wstring& message, const std::string& file, const std::string& function, int line)
{
	_com_error error(hr);
	std::wstring error_message = L"Error: " + message + L"\n" + error.ErrorMessage();
	error_message += L"\nFile: " + StringHelper::StringToWString(file);
	error_message += L"\nFunction: " + StringHelper::StringToWString(function);
	error_message += L"\nLine: " + StringHelper::StringToWString(std::to_string(line));
	MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR);
}

void ErrorLogger::Log(COMException& exception)
{
	std::wstring error_message = exception.what();
	MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR);
}
