#include "pch.h"
#include "EngineBB.h"
#include "IRenderer.h"

#include "Timer.h"
#include "KeyboardClass.h"
#include "MouseClass.h"
#include "TestOutClass.h"

#include "imgui_impl_win32.h"

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

	Timer::GetInstance()->Reset();
	Timer::GetInstance()->Start();

	m_spKeyboard = std::make_shared<KeyboardClass>();
	m_spMouse = std::make_shared<MouseClass>();

	return true;
}

bool EngineBB::Loop()
{
	Timer::GetInstance()->Tick();

	if (Timer::GetInstance()->FixFrame(60.0f) == true)
	{
		float a = Timer::GetInstance()->DeltaTime();
		DebugString::PDS("delta time : %f /ms", a);
	}
	return true;
}

void EngineBB::Finalize()
{
	if (m_spDX11Renderer) { m_spDX11Renderer->Finalize(); }

}
void EngineBB::SetInput(std::shared_ptr<__interface IInput>& _input)
{
	m_spInput = _input;
}

std::shared_ptr<__interface IInput> EngineBB::GetInput()
{
	return m_spInput;
}



extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT EngineBB::ImGuiHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
}






