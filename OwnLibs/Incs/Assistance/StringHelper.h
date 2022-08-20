#pragma once
#include <string>

/// <summary>
/// String���� �Լ�
/// 1. wstring�� string ȣȯ
/// 2. �����̸��� ������� �Լ�
/// 
/// </summary>
class StringHelper
{
public:
	static wchar_t* StringToWchar(std::string str);		// Added by YoKing

	static std::wstring StringToWString(std::string str);
	static std::string WStringToString(std::wstring str);

	static std::string GetFileName(std::string& name, bool ex);
};
