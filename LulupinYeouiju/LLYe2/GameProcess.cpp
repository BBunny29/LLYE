#include "pch.h"
#include "GameProcess.h"

#include "RenderWindow.h"
#include "Interface_EngineBB.h"
#include "Resource.h"

/// ※ 중요 함수 ※
/// WINAPI : RegisterRawInputDevices()
// 윈도우의 이벤트 리시버로 등록하는 기능을 수행

GameProcess::GameProcess()
{
	static bool raw_input_initialized = false;
	if (raw_input_initialized == false)
	{
		RAWINPUTDEVICE rid;

		rid.usUsagePage = 0x01; 
		rid.usUsage = 0x02; //Mouse
		rid.dwFlags = 0;
		rid.hwndTarget = NULL;

		if (RegisterRawInputDevices(&rid, 1, sizeof(rid)) == FALSE)
		{
			ERROR_BOX_HR(GetLastError(), "Failed to register raw input devices.");
			exit(1);
		}

		raw_input_initialized = true;
	}
}

GameProcess::~GameProcess()
{
}

bool GameProcess::Initialize(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height)
{
	/// 엔진 DLL LIB Load
	std::wstring _dllWPath;
	#ifdef _WIN64
		#ifdef _DEBUG
			_dllWPath = L"../../OwnLibs/Libs/EngineBB_x64Debug.dll";
		#else
			_dllWPath = L"EngineBB_x64Release.dll";
		#endif
	#else
		#ifdef _DEBUG
			_dllWPath = L"../../OwnLibs/Libs/EngineBB_x86Debug.dll";
		#else
			_dllWPath = L"EngineBB_x86Release.dll";
		#endif
	#endif

	//로드하기전 경로검사
	std::string _dllPath = StringHelper::WStringToString(_dllWPath);
	if (!PathFinder::IsPathExist(_dllPath))
	{
		return false;
	}

	std::shared_ptr<__interface IInput> spInput = nullptr;

	DllLoader::LoadDll<IEngineBB, IInput>(_dllWPath.c_str(), m_spEngineBB, spInput);
	
	ASSERT_NULLCHECK(m_spEngineBB, "m_spEngineBB nullptr");
	ASSERT_NULLCHECK(spInput, "spInput nullptr");

	/// 윈도우 창 초기화
	m_spRenderWindow = std::make_shared<RenderWindow>();
	
	if (!m_spRenderWindow->Initialize(this, hInstance, window_title, window_class, width, height))
	{
		return false;
	}

	/// 엔진 초기화
	if (!m_spEngineBB->Initialize((int)m_spRenderWindow->GetHWND(), width, height))
	{
		return false;
	}	

	/// Input 엔진으로 넘기고 초기화
	m_spEngineBB->SetInput(spInput);
	m_spEngineBB->GetInput()->Initialize();

	//m_spTestOutClass->FuncA();
	//m_spTestOutClass = m_spEngineBB->GetKeyInput('a');
	//int a = m_spTestOutClass->a;
	//m_spTestOutClass->a = 10;

	//m_spEngineBB->GetKeyInput('a')->FuncA();
	//m_spTestOutClass->FuncA();
	//int aa = m_spTestOutClass->a;
	
	return true;
}

void GameProcess::Finalize()
{
	if (m_spRenderWindow) { (m_spRenderWindow)->Finalize(); }
	if (m_spEngineBB) { m_spEngineBB->Finalize(); }

	//if (m_Timer) { /*(m_Timer)->Destroy();*/		delete m_Timer; m_Timer = 0; }
}

bool GameProcess::ProcessMessages()
{
	return this->m_spRenderWindow->ProcessMessages();
}

void GameProcess::Update()
{
	m_spEngineBB->Loop();			//현재 키입력 상태

	int i = 0;

}

//ImGui를 위한 핸들
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK GameProcess::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

//#ifdef _DEBUG
//
//	if (DLLEngine::ImGuiHandler(hWnd, message, wParam, lParam))
//	{
//		return true;
//
//	}
//#else
//	if (DLLEngine::ImGuiHandler(hWnd, message, wParam, lParam))
//	{
//		return true;
//	}
//#endif // DEBUG

	//if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
		//return true;

	switch (uMsg)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hwnd);
			break;
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}

		break;
	}
	case WM_SIZE:
	{
		m_spEngineBB->OnResize(LOWORD(lParam), HIWORD(lParam));
		break;
	}
	///Keyboard Messages
	case WM_KEYDOWN:
	{
		unsigned char keycode = static_cast<unsigned char>(wParam);
		m_spEngineBB->GetInput()->SetKeyboardState(eInput::Down, keycode);
		return 0;
	}
	case WM_KEYUP:
	{
		unsigned char keycode = static_cast<unsigned char>(wParam);
		m_spEngineBB->GetInput()->SetKeyboardState(eInput::Up, keycode);
		return 0;
	}
	case WM_CHAR:
	{
		unsigned char ch = static_cast<unsigned char>(wParam);
		return 0;
	}
	///Mouse Messages
	case WM_MOUSEMOVE:
	{
		POINT pos;
		pos.x = LOWORD(lParam);
		pos.y = HIWORD(lParam);
		m_spEngineBB->GetInput()->SetMousePos(pos);
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		POINT point;
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		m_spEngineBB->GetInput()->SetMouseState(eInput::Down, eMouseButtonType::Left, point);
		return 0;
	}
	case WM_RBUTTONDOWN:
	{
		POINT point;
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		m_spEngineBB->GetInput()->SetMouseState(eInput::Down, eMouseButtonType::Right, point);
		return 0;
	}
	case WM_MBUTTONDOWN:
	{
		POINT point;
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		m_spEngineBB->GetInput()->SetMouseState(eInput::Down, eMouseButtonType::Middle, point);
		return 0;
	}
	case WM_LBUTTONUP:
	{
		POINT point;
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		m_spEngineBB->GetInput()->SetMouseState(eInput::Up, eMouseButtonType::Left, point);
		return 0;
	}
	case WM_RBUTTONUP:
	{
		POINT point;
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		m_spEngineBB->GetInput()->SetMouseState(eInput::Up, eMouseButtonType::Right, point);
		return 0;
	}
	case WM_MBUTTONUP:
	{
		POINT point;
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		m_spEngineBB->GetInput()->SetMouseState(eInput::Up, eMouseButtonType::Middle, point);
		return 0;
	}
	case WM_MOUSEWHEEL:
	{
		POINT point;
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		int d = GET_WHEEL_DELTA_WPARAM(wParam);
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
		{
			m_spEngineBB->GetInput()->SetMouseWheelState(eInput::Up, point);
		}
		else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
		{
			m_spEngineBB->GetInput()->SetMouseWheelState(eInput::Down, point);
		}
		return 0;
	}
	case WM_INPUT:
	{
		UINT dataSize = 0;
		GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER)); //Need to populate data size first

		if (dataSize > 0)
		{
			std::unique_ptr<BYTE[]> rawdata = std::make_unique<BYTE[]>(dataSize);
			if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, rawdata.get(), &dataSize, sizeof(RAWINPUTHEADER)) == dataSize)
			{
				RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(rawdata.get());
				if (raw->header.dwType == RIM_TYPEMOUSE)
				{
					POINT point;
					point.x = raw->data.mouse.lLastX;
					point.y = raw->data.mouse.lLastY;
					m_spEngineBB->GetInput()->SetMouseRowPos(point);

					//m_Mouse->OnMouseMoveRaw(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
				}
			}
		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam); //Need to call DefWindowProc for WM_INPUT messages
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
