#pragma once
#include <string>

#define ERROR_BOX(message) ErrorLogger::Log(message, __FILE__, __FUNCTION__, __LINE__);
#define ERROR_BOX_HR(hr, message) if (FAILED(hr)) { ErrorLogger::Log_HR(hr, message, __FILE__, __FUNCTION__, __LINE__); }

/// <summary>
/// Error Logger 
/// 1. �޼����� ����ϴ� ErrorLogger
/// 2. HRESULT�� ����� �޼����� ����ϴ� ErrorLogger ( + ������ġ, �Լ��̸�, ��) -> string / wstring
/// 3. COMException�� �޾Ƽ� �޼����� ����ϴ� ErrorLogger
/// 
/// 2022.08.11 B.Bunny
/// </summary>
class ErrorLogger
{
public:
	static void Log(const std::string& message);
	static void Log(const std::string& message, const std::string& file, const std::string& function, int line);
	
	static void Log_HR(HRESULT hr, const std::string& message);
	static void Log_HR(HRESULT hr, const std::string& message, const std::string& file, const std::string& function, int line);
	static void LogW_HR(HRESULT hr, const std::wstring& message);
	static void LogW_HR(HRESULT hr, const std::wstring& message, const std::string& file, const std::string& function, int line);
	
	static void Log(class COMException& exception);
};