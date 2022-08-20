#pragma once
#include <windows.h>
#include <memory>
#include <string>

#include "ErrorLogger.h"

/// <summary> 
/// DLL�δ�
/// DLL�� ��������� �����Ѵ�.
/// dll�� �������̽�(.h - �Լ� ����)������ �����κ�(.cpp)�� ����ä ����Ҽ� �ִ�.
/// �õ庼Ʈ�� �������� �ϳ��� �������̽��� ���̺귯���� ������� �����־ ���� ��ƴٴ���
/// (�̷� ���ට���� �õ庼Ʈ �������� cpp�� 2000���� �Ѿ��...)
/// �� �������� �ذ��ϱ����� ���ø��� �������ڸ� ���� �������� �������̽��� ������ �ֵ��� �����غ��Ҵ� (2022.08.15 B.Bunny)
/// 
/// 2022.08.11 B.Bunny
/// </summary>

/// �� �߿� �Լ� ��
/// WINAPI : LoadLibrary()
//  �� �Լ��� ������ DLL�� �޸𸮷� �о�� ���� ���μ����� �ּ� ������ ���ν��� ����� �� �ֵ��� �ϵ� 
//  DLL�� �̹� �޸𸮿� �ö�� �ִ� ���¶�� ��� ī��Ʈ�� 1������Ų��.
//  DLL�� �о���µ� �����ϸ� DLL�� ��� �ڵ��� �����ϸ� �� �ڵ��� GetProcAddress�Լ����� ���ȴ�.
//  ���� �߻��� NULL ����

///  WINAPI : GetProcAddress()
//  DLL���� ������Ʈ�� �Լ��� ������ ã�� �� �Լ��� �Լ� �����͸� �����Ѵ�.
//  ù ��° �μ�hModule�� �Լ��� ���Ե� DLL�� ����ڵ��̰� LoadLibrary �Լ��� ������ ���̴�.
//  �ι�° lpProcName�� ã���� �ϴ� �Լ��� �̸��� ������.
//  �� �Լ����� �������̽��� �����Ҵ��ϰ� 2�� void pointer �� �װ��� �Ѱܹ޴��������� ���̺귯���� �ε��Ѵ�.

using CREATE_INSTANCE_FUNC = HRESULT(*)(void** ppv);
static HMODULE g_hExecutiveHandle;

class DllLoader
{
private:
	/// <summary>
	/// �������̽��� �Ҵ�޴� �Լ�
	/// ���̺귯���� "DllCreateInstance + �������̽��̸�" �Լ��� ������ �������̽��� �ּҰ��� (void**)�� �Ѱܹ޴´�
	/// </summary>
	template <typename T>
	static void SetInterface(std::shared_ptr<T>& Interface)
	{
		HRESULT hr;
		T* pExecutive = nullptr;

		std::string _ts2 = "�������̽� ���� ����";
		_ts2.append("\nDll interface : ");
		_ts2.append(typeid(T).name());

		// Interface�� �̸��� �˾ƿ���
		std::string _InterfaceName = typeid(T).name();
		if (_InterfaceName.substr(0, 7) == "struct ")
		{
			_InterfaceName.erase(0, 7);
		}

		// �������̽� �����͸� ��ȯ�ϴ��Լ��� + �������̽� �̸��� ���δ�.(���� ���� �ȵ�;;)
		_InterfaceName.insert(0, "DllCreateInstance");

		// �Լ�������
		CREATE_INSTANCE_FUNC pFunc;
		pFunc = (CREATE_INSTANCE_FUNC)GetProcAddress(g_hExecutiveHandle, _InterfaceName.c_str());

		hr = pFunc((void**)&pExecutive);

		if (hr != S_OK)
		{
			std::string _ts = "�������̽� ���� ����";
			_ts.append("\nDll interface : ");
			_ts.append(typeid(T).name());
			ERROR_BOX(_ts);
		}

		std::shared_ptr<T> _newPtr(pExecutive);
		Interface = _newPtr;
	}

public:
	/// <summary>
	/// Dll�� �ε��ϰ� �������̽����� ���� ���̺귯���� ������ �޾ƿ´�.
	/// �������̽��� ����(T)�� �������̽���(Interfaces)�� ������ ��ġ�ǵ��� �Ű�Ἥ �Է��Ұ� 
	/// </summary>
	/// <typeparam name="T">dll interface�� ����</typeparam>
	/// <param name="dllPath">.dll�� ��ο� �����̸�</param>
	/// <param name="Interface">.dll �������̽� �����͸� �Ҵ���� �ڸ�(��������� ������)</param>
	/// <returns></returns>
	template <typename... T>
	static inline void LoadDll(const wchar_t* dllPath, std::shared_ptr<T>& ...Interfaces)
	{
		g_hExecutiveHandle = LoadLibrary(dllPath);
		if (g_hExecutiveHandle == nullptr)
		{
			// ����â ����(dll �ε� ����)
			ERROR_BOX("dll �ε� ����");
			return;
		}

		//�������� ���� �� �Լ��� ����.
		(DllLoader::SetInterface<T>(Interfaces), ...);
	}

	/// <summary>
	/// ���̺귯�� ����
	/// </summary>
	static inline void Destroy()
	{
		// DLL ī���͸� 1���ҽ�Ű�� ��� ī��Ʈ�� 0�� �Ǿ��� ��� �޸𸮿��� DLL�� �����Ѵ�
		FreeLibrary(g_hExecutiveHandle);
	}

};


//namespace DllLoader
//{
	
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

//}
