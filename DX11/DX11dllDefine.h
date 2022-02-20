#pragma once

#ifdef _RENDERERDX11_DLL
// DLL ����
// DLL �� ����� ����  �Լ�/Ŭ�������� "export" �� ����.
#define _RDX11_DLL  __declspec(dllexport)
//#define _TEMPLATE

#else
// DLL ���
// DLL �� ����ϱ� ���� �������. "import" �� ����.
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