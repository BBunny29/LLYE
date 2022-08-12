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
		//  DLL에서 엑스포트한 함수의 번지를 찾아 그 함수의 함수 포인터를 리턴한다.
		//  첫 번째 인수hModule은 함수가 포함된 DLL의 모듈핸들이고 LoadLibrary 함수가 리턴한 값이다.
		//  두번째 lpProcName은 찾고자 하는 함수의 이름을 지정함.
		//  이 함수에서 인터페이스에 동적할당하고 2중 void pointer 로 그것을 넘겨받는형식으로 라이브러리를 로드한다.
		CREATE_INSTANCE_FUNC pFunc;
		pFunc = (CREATE_INSTANCE_FUNC)GetProcAddress(g_hExecutiveHandle,_TName.c_str());

		hr = pFunc((void**)&pExecutive);

		if (hr != S_OK)
		{
			std::string _ts = "인터페이스 생성 실패";
			_ts.append("\nDll interface : ");
			_ts.append(typeid(T).name());
			ErrorLogger::Log(_ts);
		}

		std::shared_ptr<T> _newPtr(pExecutive);
		Interface = _newPtr;
	}

	/// <summary> 
	/// DLL로더
	/// DLL을 명시적으로 연결한다.
	/// dll의 인터페이스(.h - 함수 선언)만으로 구현부분(.cpp)은 숨긴채 사용할수 있다.
	/// 시드볼트때 문제점은 하나의 인터페이스에 라이브러리의 모든기능이 몰려있어서 보기 어렵다는점(cpp는 2000줄이 넘어갔다...)
	/// 
	/// 2022.08.11 B.Bunny
	/// </summary>
	/// <typeparam name="T">dll interface의 이름</typeparam>
	/// <param name="dllPath">.dll의 경로와 파일이름</param>
	/// <returns></returns>
	template <typename... argsT>
	inline void LoadDll(const wchar_t* dllPath, std::shared_ptr<argsT>& ...Interface)
	{
		/// LoadLibrary
		//  이 함수는 지정한 DLL을 메모리로 읽어와 현재 프로세스의 주소 공간에 맵핑시켜 사용할 수 있도록 하되 
		//  DLL이 이미 메모리에 올라와 있는 상태라면 사용 카운트만 1증가시킨다.
		//  DLL을 읽어오는데 성공하면 DLL의 모듈 핸들을 리턴하며 이 핸들은 GetProcAddress함수에서 사용된다.
		//  에러 발생시 NULL 리턴			
		g_hExecutiveHandle = LoadLibrary(dllPath);
		if (g_hExecutiveHandle == nullptr)
		{
			// 오류창 띄우기(dll 로드 실패)
			return;
		}
		
		//가변인자 전부 이 함수를 돈다.
		(doSomething<argsT>(Interface), ...);
	}


	//template <typename T>
	//inline std::shared_ptr<T> LoadDll(const wchar_t* dllPath)
	//{
	//	T* pExecutive;
	//	HRESULT hr;
	//
	//	/// LoadLibrary
	//	//  이 함수는 지정한 DLL을 메모리로 읽어와 현재 프로세스의 주소 공간에 맵핑시켜 사용할 수 있도록 하되 
	//	//  DLL이 이미 메모리에 올라와 있는 상태라면 사용 카운트만 1증가시킨다.
	//	//  DLL을 읽어오는데 성공하면 DLL의 모듈 핸들을 리턴하며 이 핸들은 GetProcAddress함수에서 사용된다.
	//	//  에러 발생시 NULL 리턴			
	//	g_hExecutiveHandle = LoadLibrary(dllPath);
	//	if (g_hExecutiveHandle == nullptr)
	//	{
	//		return nullptr;
	//	}
	//
	//	/// GetProcAddress
	//	//  DLL에서 엑스포트한 함수의 번지를 찾아 그 함수의 함수 포인터를 리턴한다.
	//	//  첫 번째 인수hModule은 함수가 포함된 DLL의 모듈핸들이고 LoadLibrary 함수가 리턴한 값이다.
	//	//  두번째 lpProcName은 찾고자 하는 함수의 이름을 지정함.
	//	//  이 함수에서 인터페이스에 동적할당하고 2중 void pointer 로 그것을 넘겨받는형식으로 라이브러리를 로드한다.
	//	CREATE_INSTANCE_FUNC pFunc;
	//	pFunc = (CREATE_INSTANCE_FUNC)GetProcAddress(g_hExecutiveHandle, "DllCreateInstance");
	//
	//	hr = pFunc((void**)&pExecutive);
	//	
	//	if (hr != S_OK)
	//	{
	//		std::string _ts = "DLL 로드/생성 실패";
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
	//	//  이 함수는 지정한 DLL을 메모리로 읽어와 현재 프로세스의 주소 공간에 맵핑시켜 사용할 수 있도록 하되 
	//	//  DLL이 이미 메모리에 올라와 있는 상태라면 사용 카운트만 1증가시킨다.
	//	//  DLL을 읽어오는데 성공하면 DLL의 모듈 핸들을 리턴하며 이 핸들은 GetProcAddress함수에서 사용된다.
	//	//  에러 발생시 NULL 리턴			
	//	g_hExecutiveHandle = LoadLibrary(dllPath);
	//	if (g_hExecutiveHandle == nullptr)
	//	{
	//		return nullptr;
	//	}
	//
	//	/// GetProcAddress
	//	//  DLL에서 엑스포트한 함수의 번지를 찾아 그 함수의 함수 포인터를 리턴한다.
	//	//  첫 번째 인수hModule은 함수가 포함된 DLL의 모듈핸들이고 LoadLibrary 함수가 리턴한 값이다.
	//	//  두번째 lpProcName은 찾고자 하는 함수의 이름을 지정함.
	//	//  이 함수에서 인터페이스에 동적할당하고 2중 void pointer 로 그것을 넘겨받는형식으로 라이브러리를 로드한다.
	//	CREATE_INSTANCE_FUNC pFunc;
	//	pFunc = (CREATE_INSTANCE_FUNC)GetProcAddress(g_hExecutiveHandle, "DllCreateInstance");
	//
	//	hr = pFunc((void**)&pExecutive);
	//	
	//	if (hr != S_OK)
	//	{
	//		std::string _ts = "DLL 로드/생성 실패";
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
		// DLL 카운터를 1감소시키며 사용 카운트가 0이 되었을 경우 메모리에서 DLL을 삭제한다
		FreeLibrary(g_hExecutiveHandle);
	}
}
