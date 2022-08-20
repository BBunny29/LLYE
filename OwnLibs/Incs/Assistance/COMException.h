#pragma once
#include <comdef.h>
#include <string>

#define THROW_COM_ERROR_IF_FAILED( hr, msg ) if (FAILED(hr)) throw COMException(hr, msg, __FILE__, __FUNCTION__, __LINE__)

/// <summary>
/// Error Throw하기위한 class
/// 
/// 2022.08.11 B.Bunny
/// </summary>
class COMException
{
public:
	COMException(HRESULT hr, const std::string& msg, const std::string& file, const std::string& function, int line);

	const wchar_t* what() const;

private:
	std::wstring whatmsg;
};
