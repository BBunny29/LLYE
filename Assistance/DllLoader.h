#pragma once
#include "pch.h"
#include "ErrorLogger.h"

#include <vector>
#include "DebugString.h"

static HMODULE g_hExecutiveHandle;
using CREATE_INSTANCE_FUNC = HRESULT(*)(void** ppv);

namespace DllLoader
{
	template <typename T>
	void doSomething(std::shared_ptr<T>& Interface)
	{		
		HRESULT hr;
		T* pExecutive;
		
		std::string _TName = typeid(T).name();
		if (_TName.substr(0, 7) == "struct ")
		{
			_TName.erase(0, 7);
		}
		_TName.insert(0,"DllCreateInstance");
		/// GetProcAddress
		//  DLL���� ������Ʈ�� �Լ��� ������ ã�� �� �Լ��� �Լ� �����͸� �����Ѵ�.
		//  ù ��° �μ�hModule�� �Լ��� ���Ե� DLL�� ����ڵ��̰� LoadLibrary �Լ��� ������ ���̴�.
		//  �ι�° lpProcName�� ã���� �ϴ� �Լ��� �̸��� ������.
		//  �� �Լ����� �������̽��� �����Ҵ��ϰ� 2�� void pointer �� �װ��� �Ѱܹ޴��������� ���̺귯���� �ε��Ѵ�.
		CREATE_INSTANCE_FUNC pFunc;
		pFunc = (CREATE_INSTANCE_FUNC)GetProcAddress(g_hExecutiveHandle,_TName.c_str());

		hr = pFunc((void**)&pExecutive);

		if (hr != S_OK)
		{
			std::string _ts = "�������̽� ���� ����";
			_ts.append("\nDll interface : ");
			_ts.append(typeid(T).name());
			ErrorLogger::Log(_ts);
		}

		std::shared_ptr<T> _newPtr(pExecutive);
		Interface = _newPtr;
	}

	/// <summary> 
	/// DLL�δ�
	/// DLL�� ��������� �����Ѵ�.
	/// dll�� �������̽�(.h - �Լ� ����)������ �����κ�(.cpp)�� ����ä ����Ҽ� �ִ�.
	/// �õ庼Ʈ�� �������� �ϳ��� �������̽��� ���̺귯���� ������� �����־ ���� ��ƴٴ���(cpp�� 2000���� �Ѿ��...)
	/// 
	/// 2022.08.11 B.Bunny
	/// </summary>
	/// <typeparam name="T">dll interface�� �̸�</typeparam>
	/// <param name="dllPath">.dll�� ��ο� �����̸�</param>
	/// <returns></returns>
	template <typename... argsT>
	inline void LoadDll(const wchar_t* dllPath, std::shared_ptr<argsT>& ...Interface)
	{
		/// LoadLibrary
		//  �� �Լ��� ������ DLL�� �޸𸮷� �о�� ���� ���μ����� �ּ� ������ ���ν��� ����� �� �ֵ��� �ϵ� 
		//  DLL�� �̹� �޸𸮿� �ö�� �ִ� ���¶�� ��� ī��Ʈ�� 1������Ų��.
		//  DLL�� �о���µ� �����ϸ� DLL�� ��� �ڵ��� �����ϸ� �� �ڵ��� GetProcAddress�Լ����� ���ȴ�.
		//  ���� �߻��� NULL ����			
		g_hExecutiveHandle = LoadLibrary(dllPath);
		if (g_hExecutiveHandle == nullptr)
		{
			// ����â ����(dll �ε� ����)
			return;
		}
		
		//�������� ���� �� �Լ��� ����.
		(doSomething<argsT>(Interface), ...);
	}


	//template <typename T>
	//inline std::shared_ptr<T> LoadDll(const wchar_t* dllPath)
	//{
	//	T* pExecutive;
	//	HRESULT hr;
	//
	//	/// LoadLibrary
	//	//  �� �Լ��� ������ DLL�� �޸𸮷� �о�� ���� ���μ����� �ּ� ������ ���ν��� ����� �� �ֵ��� �ϵ� 
	//	//  DLL�� �̹� �޸𸮿� �ö�� �ִ� ���¶�� ��� ī��Ʈ�� 1������Ų��.
	//	//  DLL�� �о���µ� �����ϸ� DLL�� ��� �ڵ��� �����ϸ� �� �ڵ��� GetProcAddress�Լ����� ���ȴ�.
	//	//  ���� �߻��� NULL ����			
	//	g_hExecutiveHandle = LoadLibrary(dllPath);
	//	if (g_hExecutiveHandle == nullptr)
	//	{
	//		return nullptr;
	//	}
	//
	//	/// GetProcAddress
	//	//  DLL���� ������Ʈ�� �Լ��� ������ ã�� �� �Լ��� �Լ� �����͸� �����Ѵ�.
	//	//  ù ��° �μ�hModule�� �Լ��� ���Ե� DLL�� ����ڵ��̰� LoadLibrary �Լ��� ������ ���̴�.
	//	//  �ι�° lpProcName�� ã���� �ϴ� �Լ��� �̸��� ������.
	//	//  �� �Լ����� �������̽��� �����Ҵ��ϰ� 2�� void pointer �� �װ��� �Ѱܹ޴��������� ���̺귯���� �ε��Ѵ�.
	//	CREATE_INSTANCE_FUNC pFunc;
	//	pFunc = (CREATE_INSTANCE_FUNC)GetProcAddress(g_hExecutiveHandle, "DllCreateInstance");
	//
	//	hr = pFunc((void**)&pExecutive);
	//	
	//	if (hr != S_OK)
	//	{
	//		std::string _ts = "DLL �ε�/���� ����";
	//		_ts.append("\nDll interface : ");
	//		_ts.append(typeid(T).name());
	//		ErrorLogger::Log(_ts);
	//
	//		return nullptr;
	//	}
	//
	//	std::shared_ptr<T> _newPtr(pExecutive);
	//
	//	return _newPtr;
	//}

	//template <typename T>
	//inline std::shared_ptr<T> LoadDll(const wchar_t* dllPath)
	//{
	//	T* pExecutive;
	//	HRESULT hr;
	//
	//	/// LoadLibrary
	//	//  �� �Լ��� ������ DLL�� �޸𸮷� �о�� ���� ���μ����� �ּ� ������ ���ν��� ����� �� �ֵ��� �ϵ� 
	//	//  DLL�� �̹� �޸𸮿� �ö�� �ִ� ���¶�� ��� ī��Ʈ�� 1������Ų��.
	//	//  DLL�� �о���µ� �����ϸ� DLL�� ��� �ڵ��� �����ϸ� �� �ڵ��� GetProcAddress�Լ����� ���ȴ�.
	//	//  ���� �߻��� NULL ����			
	//	g_hExecutiveHandle = LoadLibrary(dllPath);
	//	if (g_hExecutiveHandle == nullptr)
	//	{
	//		return nullptr;
	//	}
	//
	//	/// GetProcAddress
	//	//  DLL���� ������Ʈ�� �Լ��� ������ ã�� �� �Լ��� �Լ� �����͸� �����Ѵ�.
	//	//  ù ��° �μ�hModule�� �Լ��� ���Ե� DLL�� ����ڵ��̰� LoadLibrary �Լ��� ������ ���̴�.
	//	//  �ι�° lpProcName�� ã���� �ϴ� �Լ��� �̸��� ������.
	//	//  �� �Լ����� �������̽��� �����Ҵ��ϰ� 2�� void pointer �� �װ��� �Ѱܹ޴��������� ���̺귯���� �ε��Ѵ�.
	//	CREATE_INSTANCE_FUNC pFunc;
	//	pFunc = (CREATE_INSTANCE_FUNC)GetProcAddress(g_hExecutiveHandle, "DllCreateInstance");
	//
	//	hr = pFunc((void**)&pExecutive);
	//	
	//	if (hr != S_OK)
	//	{
	//		std::string _ts = "DLL �ε�/���� ����";
	//		_ts.append("\nDll interface : ");
	//		_ts.append(typeid(T).name());
	//		ErrorLogger::Log(_ts);
	//
	//		return nullptr;
	//	}
	//
	//	std::shared_ptr<T> _newPtr(pExecutive);
	//
	//	return _newPtr;
	//}


	/// <summary>
	/// 
	/// </summary>
	inline void Destroy()
	{
		// DLL ī���͸� 1���ҽ�Ű�� ��� ī��Ʈ�� 0�� �Ǿ��� ��� �޸𸮿��� DLL�� �����Ѵ�
		FreeLibrary(g_hExecutiveHandle);
	}
}
