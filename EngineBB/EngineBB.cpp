#include "pch.h"
#include "EngineBB.h"
#include "IRenderer.h"

#include "Timer.h"

#include "imgui_impl_win32.h"
#include "ComponentSystem.h"

EngineBB::EngineBB()
{
}

EngineBB::~EngineBB()
{
}

bool EngineBB::Initialize(int hWND, int width, int height)
{
	m_hWND = reinterpret_cast<HWND>(hWND);;
	m_width = width;
	m_height = height;

	/// 렌더러 DLL LIB Load
	std::wstring _RendererDllWPath;
	#ifdef _WIN64
		#ifdef _DEBUG
			_RendererDllWPath = L"../../OwnLibs/Libs/DX11_x64Debug.dll";
		#else
			_RendererDllWPath = L"DX11_x64Release.dll";
		#endif
	#else
		#ifdef _DEBUG
			_RendererDllWPath = L"../../OwnLibs/Libs/DX11_x86Debug.dll";
		#else
			_RendererDllWPath = L"DX11_x86Release.dll";
		#endif
	#endif

	// 로드하기전 경로검사
	std::string _RendererDllPath = StringHelper::WStringToString(_RendererDllWPath);
	if (!PathFinder::IsPathExist(_RendererDllPath))
	{
		return false;
	}

	DllLoader::LoadDll<IRenderer>(_RendererDllWPath.c_str(), m_spDX11Renderer);
	// 널포인터 체크
	ASSERT_NULLCHECK(m_spDX11Renderer, "DX11Renderer nullptr");

	if (!m_spDX11Renderer->Initialize(hWND, width, height))
	{
		return false;
	}

	/// 리소스 매니저 DLL LIB Load
	std::wstring _ResourceManagerDllWPath;
	#ifdef _WIN64
		#ifdef _DEBUG
			_ResourceManagerDllWPath = L"../../OwnLibs/Libs/ResourceManager_x64Debug.dll";
		#else
			_ResourceManagerDllWPath = L"ResourceManager_x64Release.dll";
		#endif
	#else
		#ifdef _DEBUG
			_ResourceManagerDllWPath = L"../../OwnLibs/Libs/ResourceManager_x86Debug.dll";
		#else
			_ResourceManagerDllWPath = L"ResourceManager_x86Release.dll";
		#endif
	#endif

	// 로드하기전 경로검사
	std::string _ResourceManagerDllPath = StringHelper::WStringToString(_ResourceManagerDllWPath);
	if (!PathFinder::IsPathExist(_ResourceManagerDllPath))
	{
		return false;
	}

	DllLoader::LoadDll<IResourceManager>(_ResourceManagerDllWPath.c_str(), m_spResourceManager);
	// 널포인터 체크
	ASSERT_NULLCHECK(m_spResourceManager, "ResourceManager nullptr");

	if (!m_spResourceManager->Initialize(m_spDX11Renderer))
	{
		return false;
	}

	m_spComponentManager = std::make_shared<ComponentSystem>();
	m_spComponentManager->SetResourceManager(m_spResourceManager);

	/// 타이머 셋팅
	Timer::GetInstance()->Reset();
	Timer::GetInstance()->Start();

	return true;
}

bool EngineBB::Loop()
{
	Timer::GetInstance()->Tick();

	if (Timer::GetInstance()->FixFrame(60.0f) == true)
	{
		float a = Timer::GetInstance()->DeltaTime();
		
		unsigned char bb = static_cast<unsigned char>(eKey::KEY_ESCAPE);
		bool b = m_spInput->IsKeyUp(bb); 
		if (b == true)
		{
			DebugString::PDS("input a press? : %d", b);
		}
		
		UpdateAll(Timer::GetInstance()->DeltaTime());
		RenderAll();

		// 가장 나중에 키입력 업데이트를 한다.
		m_spInput->Update();
	}
	return true;
}

void EngineBB::Finalize()
{
	if (m_spDX11Renderer) { m_spDX11Renderer->Finalize(); }

}
void EngineBB::OnResize(int width, int height)
{
	m_width = width;
	m_height = height;

	if (m_spDX11Renderer != nullptr)
	{
		m_spDX11Renderer->OnResize(width, height);
	}
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

int EngineBB::GetScreenWidth()
{
	return m_width;
}

int EngineBB::GetScreenHeight()
{
	return m_height;
}

HWND EngineBB::GetHWND()
{
	return m_hWND;
}

void EngineBB::UpdateAll(float dTime)
{
	m_spComponentManager->Update(dTime);
}

void EngineBB::RenderAll()
{
	m_spDX11Renderer->BeginRender();
	m_spDX11Renderer->Render();
	m_spDX11Renderer->EndRender();
}
