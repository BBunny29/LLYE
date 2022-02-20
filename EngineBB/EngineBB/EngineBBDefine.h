#pragma once
# include "EngineBBLibraryDefine.h"

#ifdef _ENGINEBB_DLL
// DLL ����
// DLL �� ����� ����  �Լ�/Ŭ�������� "export" �� ����.
#define _EBB_DLL  __declspec(dllexport)
//#define _TEMPLATE

#else
// DLL ���
// DLL �� ����ϱ� ���� �������. "import" �� ����.
#define _EBB_DLL  __declspec(dllimport)
//#define _TEMPLATE extern

#ifdef _WIN64
#ifdef _DEBUG
#pragma comment(lib, "EngineBB_x64Debug.lib")		//64bit + debug

#else
#pragma comment(lib, "EngineBB_x64Release.lib")	//64bit.

#endif 
#endif   
#endif