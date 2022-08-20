#include "pch.h"
#include "StringHelper.h"

#include <locale>

/// <summary>
/// std::string 을 wchar_t* 로 바꿔 리턴
/// 단 만들어서 리턴은 해주지만 해제는 여기서 할 수 없으므로
/// 호출한 쪽에서 잘 사용하고 반드시 해제해줘야 할 것이다..
/// (매우 위험해 보이는데?)
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
wchar_t* StringHelper::StringToWchar(std::string str)
{
	// 지역 설정, 안하면 한글이 깨지게 된다..
	setlocale(LC_ALL, "Korean");

	// 사이즈 구하고
	const size_t cSize = strlen(str.c_str()) + 1;

	// 사이즈만큼 동적할당
	wchar_t* text = new wchar_t[cSize];

	// std::string 을 wchar_t로 변환해서 text에 넣는다
	mbstowcs_s(nullptr, text, cSize, str.c_str(), cSize);

	// 호출한쪽에서 사용하고 반드시 delete 해줘야 메모리릭 안날것이다....
	return text;
}

std::wstring StringHelper::StringToWString(std::string str)
{
	std::wstring wide_string(str.begin(), str.end());
	return wide_string;
}

std::string StringHelper::WStringToString(std::wstring str)
{
	std::string _nowString(str.begin(), str.end());
	return _nowString;
}

/// <summary>
/// 경로명에서 파일이름만 반환한다.
/// 파일이 아닐경우(확장자가 없는경우) 비어있는 string을 반환한다.
/// ex가 true일 경우 확장자를 붙여준다
/// </summary>
/// <param name="path"></param>
/// <param name="ex"></param>
/// <returns></returns>
std::string StringHelper::GetFileName(std::string& path, bool ex)
{
	std::string result;
	std::string extension;
	size_t sizeOfPath = path.size();
	size_t extensionSize = 0;

	for (size_t i = sizeOfPath - 1; i > 0; i--)
	{
		// 확장자명을 자른다.
		if (path.at(i) == '.')
		{
			extension = path.substr(i, sizeOfPath - i);
			extensionSize = sizeOfPath - i;
		}

		// 파일명을 잘라낸다.
		if (path.at(i) == '/' || path.at(i) == '\\')
		{
			// 확장자가 없으면 파일명이 아님
			if (extension.size() == 0)
			{
				return std::string();
			}

			result = path.substr(i + 1, sizeOfPath - (i + 1) - extensionSize);
			break;
		}
	}

	if (ex == true)
	{
		result.append(extension);
		return result;
	}
	else
	{
		return result;
	}
}