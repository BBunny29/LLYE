#include "pch.h"
#include "EngineBB.h"
#include "IRenderer.h"

#include "Timer.h"
//#include "KeyboardClass.h"
//#include "MouseClass.h"

EngineBB::EngineBB()
{
}

EngineBB::~EngineBB()
{
}

bool EngineBB::Initialize(int hWND, int width, int height)
{
	/// 렌더러 DLL LIB Load
	std::wstring _dllWPath;
	#ifdef _WIN64
		#ifdef _DEBUG
			_dllWPath = L"../../OwnLibs/Libs/DX11_x64Debug.dll";
		#else
			_dllWPath = L"DX11_x64Release.dll";
		#endif
	#else
		#ifdef _DEBUG
			_dllWPath = L"../../OwnLibs/Libs/DX11_x86Debug.dll";
		#else
			_dllWPath = L"DX11_x86Release.dll";
		#endif
	#endif

	//로드하기전 경로검사
	std::string _dllPath = StringHelper::WStringToString(_dllWPath);
	if (!PathFinder::IsPathExist(_dllPath))
	{
		return false;
	}

	DllLoader::LoadDll<IRenderer>(_dllWPath.c_str(), m_spDX11Renderer);
	// 널포인터 체크
	ASSERT_NULLCHECK(m_spDX11Renderer, "DX11Renderer nullptr");

	if (!m_spDX11Renderer->Initialize(hWND, width, height))
	{
		return false;
	}

	return true;
}

void EngineBB::Finalize()
{
	if (m_spDX11Renderer) { m_spDX11Renderer->Finalize(); }

}
