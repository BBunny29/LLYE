#include "pch.h"
#include "StringHelper.h"

#include <locale>

/// <summary>
/// std::string �� wchar_t* �� �ٲ� ����
/// �� ���� ������ �������� ������ ���⼭ �� �� �����Ƿ�
/// ȣ���� �ʿ��� �� ����ϰ� �ݵ�� ��������� �� ���̴�..
/// (�ſ� ������ ���̴µ�?)
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
wchar_t* StringHelper::StringToWchar(std::string str)
{
	// ���� ����, ���ϸ� �ѱ��� ������ �ȴ�..
	setlocale(LC_ALL, "Korean");

	// ������ ���ϰ�
	const size_t cSize = strlen(str.c_str()) + 1;

	// �����ŭ �����Ҵ�
	wchar_t* text = new wchar_t[cSize];

	// std::string �� wchar_t�� ��ȯ�ؼ� text�� �ִ´�
	mbstowcs_s(nullptr, text, cSize, str.c_str(), cSize);

	// ȣ�����ʿ��� ����ϰ� �ݵ�� delete ����� �޸𸮸� �ȳ����̴�....
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
/// ��θ��� �����̸��� ��ȯ�Ѵ�.
/// ������ �ƴҰ��(Ȯ���ڰ� ���°��) ����ִ� string�� ��ȯ�Ѵ�.
/// ex�� true�� ��� Ȯ���ڸ� �ٿ��ش�
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
		// Ȯ���ڸ��� �ڸ���.
		if (path.at(i) == '.')
		{
			extension = path.substr(i, sizeOfPath - i);
			extensionSize = sizeOfPath - i;
		}

		// ���ϸ��� �߶󳽴�.
		if (path.at(i) == '/' || path.at(i) == '\\')
		{
			// Ȯ���ڰ� ������ ���ϸ��� �ƴ�
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