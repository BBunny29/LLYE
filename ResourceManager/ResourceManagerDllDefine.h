#pragma once

#ifdef _RESOURCEMANAGER_DLL
// DLL ����
// DLL �� ����� ����  �Լ�/Ŭ�������� "export" �� ����.
#define _RESORCE_DLL  __declspec(dllexport)
//#define _TEMPLATE

#else
// DLL ���
// DLL �� ����ϱ� ���� �������. "import" �� ����.
#define _RESORCE_DLL  __declspec(dllimport)
//#define _TEMPLATE extern

#ifdef _WIN64
#ifdef _DEBUG
#pragma comment(lib, "ResourceManager_x64Debug.lib")		//64bit + debug
#else
#pragma comment(lib, "ResourceManager_x64Release.lib")		//64bit.
#endif 
#endif
#endif