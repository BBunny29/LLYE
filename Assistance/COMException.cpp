#include "pch.h"
#include "COMException.h"

#include "StringHelper.h"
//#include "CATrace.h"

COMException::COMException(HRESULT hr, const std::string& msg, const std::string& file, const std::string& function, int line)
{
	_com_error error(hr);
	whatmsg = L"Msg: " + StringHelper::StringToWString(std::string(msg)) + L"\n";
	whatmsg += error.ErrorMessage();
	whatmsg += L"\nFile: " + StringHelper::StringToWString(file);
	whatmsg += L"\nFunction: " + StringHelper::StringToWString(function);
	whatmsg += L"\nLine: " + StringHelper::StringToWString(std::to_string(line));
}

const wchar_t* COMException::what() const
{
	return  whatmsg.c_str();
}

//RESOURCE_MISSING_Exception::RESOURCE_MISSING_Exception(const std::string& msg)
//{
//	CA_TRACE(msg.c_str());
//}
//
//NULLNameException::NULLNameException(const std::string& msg)
//{
//	CA_TRACE(msg.c_str());
//}


