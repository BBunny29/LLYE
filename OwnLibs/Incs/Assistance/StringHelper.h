#pragma once
#include <string>

/// <summary>
/// String관련 함수
/// 1. wstring과 string 호환
/// 2. 파일이름만 떼어오는 함수
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
