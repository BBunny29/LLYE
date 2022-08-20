#pragma once
#include <windows.h>
#include <memory>
#include <string>

#include "ErrorLogger.h"

/// <summary> 
/// DLL로더
/// DLL을 명시적으로 연결한다.
/// dll의 인터페이스(.h - 함수 선언)만으로 구현부분(.cpp)은 숨긴채 사용할수 있다.
/// 시드볼트때 문제점은 하나의 인터페이스에 라이브러리의 모든기능이 몰려있어서 보기 어렵다는점
/// (이런 제약때문에 시드볼트 렌더러의 cpp는 2000줄이 넘어갔다...)
/// 이 문제점을 해결하기위해 템플릿과 가변인자를 통해 여러개의 인터페이스를 가질수 있도록 개선해보았다 (2022.08.15 B.Bunny)
/// 
/// 2022.08.11 B.Bunny
/// </summary>

/// ※ 중요 함수 ※
/// WINAPI : LoadLibrary()
//  이 함수는 지정한 DLL을 메모리로 읽어와 현재 프로세스의 주소 공간에 맵핑시켜 사용할 수 있도록 하되 
//  DLL이 이미 메모리에 올라와 있는 상태라면 사용 카운트만 1증가시킨다.
//  DLL을 읽어오는데 성공하면 DLL의 모듈 핸들을 리턴하며 이 핸들은 GetProcAddress함수에서 사용된다.
//  에러 발생시 NULL 리턴

///  WINAPI : GetProcAddress()
//  DLL에서 엑스포트한 함수의 번지를 찾아 그 함수의 함수 포인터를 리턴한다.
//  첫 번째 인수hModule은 함수가 포함된 DLL의 모듈핸들이고 LoadLibrary 함수가 리턴한 값이다.
//  두번째 lpProcName은 찾고자 하는 함수의 이름을 지정함.
//  이 함수에서 인터페이스에 동적할당하고 2중 void pointer 로 그것을 넘겨받는형식으로 라이브러리를 로드한다.

using CREATE_INSTANCE_FUNC = HRESULT(*)(void** ppv);
static HMODULE g_hExecutiveHandle;

class DllLoader
{
private:
	/// <summary>
	/// 인터페이스를 할당받는 함수
	/// 라이브러리의 "DllCreateInstance + 인터페이스이름" 함수에 접근해 인터페이스의 주소값을 (void**)로 넘겨받는다
	/// </summary>
	template <typename T>
	static void SetInterface(std::shared_ptr<T>& Interface)
	{
		HRESULT hr;
		T* pExecutive = nullptr;

		std::string _ts2 = "인터페이스 생성 실패";
		_ts2.append("\nDll interface : ");
		_ts2.append(typeid(T).name());

		// Interface의 이름을 알아오기
		std::string _InterfaceName = typeid(T).name();
		if (_InterfaceName.substr(0, 7) == "struct ")
		{
			_InterfaceName.erase(0, 7);
		}

		// 인터페이스 포인터를 반환하는함수명 + 인터페이스 이름을 붙인다.(별로 맘에 안듦;;)
		_InterfaceName.insert(0, "DllCreateInstance");

		// 함수포인터
		CREATE_INSTANCE_FUNC pFunc;
		pFunc = (CREATE_INSTANCE_FUNC)GetProcAddress(g_hExecutiveHandle, _InterfaceName.c_str());

		hr = pFunc((void**)&pExecutive);

		if (hr != S_OK)
		{
			std::string _ts = "인터페이스 생성 실패";
			_ts.append("\nDll interface : ");
			_ts.append(typeid(T).name());
			ERROR_BOX(_ts);
		}

		std::shared_ptr<T> _newPtr(pExecutive);
		Interface = _newPtr;
	}

public:
	/// <summary>
	/// Dll을 로드하고 인터페이스들을 통해 라이브러리의 내용을 받아온다.
	/// 인터페이스의 형식(T)과 인터페이스들(Interfaces)의 순서가 매치되도록 신경써서 입력할것 
	/// </summary>
	/// <typeparam name="T">dll interface의 형식</typeparam>
	/// <param name="dllPath">.dll의 경로와 파일이름</param>
	/// <param name="Interface">.dll 인터페이스 포인터를 할당받을 자리(멤버변수의 포인터)</param>
	/// <returns></returns>
	template <typename... T>
	static inline void LoadDll(const wchar_t* dllPath, std::shared_ptr<T>& ...Interfaces)
	{
		g_hExecutiveHandle = LoadLibrary(dllPath);
		if (g_hExecutiveHandle == nullptr)
		{
			// 오류창 띄우기(dll 로드 실패)
			ERROR_BOX("dll 로드 실패");
			return;
		}

		//가변인자 전부 이 함수를 돈다.
		(DllLoader::SetInterface<T>(Interfaces), ...);
	}

	/// <summary>
	/// 라이브러리 해제
	/// </summary>
	static inline void Destroy()
	{
		// DLL 카운터를 1감소시키며 사용 카운트가 0이 되었을 경우 메모리에서 DLL을 삭제한다
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

//}
