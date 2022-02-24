#pragma once

#ifdef _RENDERERDX11_DLL
// DLL 제작
// DLL 을 만들기 위해  함수/클래스등을 "export" 로 선언.
#define _RDX11_DLL  __declspec(dllexport)
//#define _TEMPLATE

#else
// DLL 사용
// DLL 을 사용하기 위한 헤더파일. "import" 로 선언.
#define _RDX11_DLL  __declspec(dllimport)
//#define _TEMPLATE extern

#ifdef _WIN64
#ifdef _DEBUG
#pragma comment(lib, "DX11_x64Debug.lib")		//64bit + debug

#else
#pragma comment(lib, "DX11_x64Release.lib")	//64bit.

#endif 
#endif   
#endif