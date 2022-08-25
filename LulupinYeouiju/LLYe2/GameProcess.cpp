#include "pch.h"
#include "GameProcess.h"

#include "RenderWindow.h"
#include "TestOutClass.h"
#include "IEngineBB.h"

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

	std::shared_ptr<__interface ITestOutClass> spTestOutClass = nullptr;

	//DllLoader::LoadDll<IEngineBB>(_dllWPath.c_str(), m_spEngineBB);
	DllLoader::LoadDll<IEngineBB, ITestOutClass>(_dllWPath.c_str(), m_spEngineBB, spTestOutClass);
	ASSERT_NULLCHECK(m_spEngineBB, "m_spEngineBB nullptr");
	//ASSERT_NULLCHECK(m_spTestOutClass, "m_spTestOutClass nullptr");

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

	m_spEngineBB->SetKeyInput(spTestOutClass);
	
	
	m_spEngineBB->GetKeyInput('a')->FuncA();
	
	
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

	//if (m_Keyboard) { /*(m_Keyboard)->Destroy();*/	delete m_Keyboard; m_Keyboard = 0; }
	//if (m_Mouse) { /*(m_Mouse)->Destroy();*/		delete m_Mouse; m_Mouse = 0; }
	//if (m_Timer) { /*(m_Timer)->Destroy();*/		delete m_Timer; m_Timer = 0; }
}

bool GameProcess::ProcessMessages()
{
	return this->m_spRenderWindow->ProcessMessages();
}

void GameProcess::Update()
{
	m_spEngineBB->Loop();

//	float deltaTime = m_Timer->GetMilisecondesElapsed();
//	m_Timer->Restart();
//
//#ifdef _DEBUG
//	while (!m_Keyboard->CharBufferIsEmpty())
//	{
//		unsigned char ch = m_Keyboard->ReadChar();
//		std::string outmsg = "Char : ";
//		outmsg += ch;
//		outmsg += "\n";
//		OutputDebugStringA(outmsg.c_str());
//	}
//
//	while (!m_Keyboard->KeyBufferIsEmpty())
//	{
//		KeyboardEvent* kbe = new KeyboardEvent();
//		kbe = m_Keyboard->ReadKey();
//		unsigned char keycode = kbe->GetKeyCode();
//
//		std::string outmsg = "KeyCode : ";
//		if (kbe->IsPress())
//		{
//			outmsg += "Key Press : ";
//		}
//		if (kbe->IsRelease())
//		{
//			outmsg += "Key Release : ";
//		}
//		outmsg += keycode;
//		outmsg += "\n";
//		OutputDebugStringA(outmsg.c_str());
//	}
//#endif // _DEBUG
//
//	const float camera3DSpeed = 0.01f;
//
//	///마우스
//	while (!m_Mouse->EventBufferIsEmpty())
//	{
//		MouseEvent me = m_Mouse->ReadEvent();
//		if (m_Mouse->IsRightDown())
//		{
//			if (me.GetType() == MouseEvent::EventType::RAW_MOVE)
//			{
//				g_Renderer->m_pCamera3D->AdjustRotation((float)me.GetPosY() * 0.01f, (float)me.GetPosX() * 0.01f, 0);
//			}
//		}
//	}
//
//
//	///키보드
//	if (m_Keyboard->KeyIsPressed('W'))
//	{
//		g_Renderer->m_pCamera3D->AdjustPosition(g_Renderer->m_pCamera3D->GetForwardVector() * camera3DSpeed * deltaTime);
//	}
//	if (m_Keyboard->KeyIsPressed('S'))
//	{
//		g_Renderer->m_pCamera3D->AdjustPosition(g_Renderer->m_pCamera3D->GetBackwardVector() * camera3DSpeed * deltaTime);
//	}
//	if (m_Keyboard->KeyIsPressed('A'))
//	{
//		g_Renderer->m_pCamera3D->AdjustPosition(g_Renderer->m_pCamera3D->GetLeftVector() * camera3DSpeed * deltaTime);
//	}
//	if (m_Keyboard->KeyIsPressed('D'))
//	{
//		g_Renderer->m_pCamera3D->AdjustPosition(g_Renderer->m_pCamera3D->GetRightVector() * camera3DSpeed * deltaTime);
//	}
//	if (m_Keyboard->KeyIsPressed('E'))
//	{
//		g_Renderer->m_pCamera3D->AdjustPosition(0.0f, camera3DSpeed * deltaTime, 0.0f);
//	}
//	if (m_Keyboard->KeyIsPressed('Q'))
//	{
//		g_Renderer->m_pCamera3D->AdjustPosition(0.0f, -camera3DSpeed * deltaTime, 0.0f);
//	}
//
//	if (m_Keyboard->KeyIsPressed(VK_LEFT))	// left
//	{
//		//g_gfx->gameObject.AdjustPosition(-0.05f * deltaTime, 0.0f, 0.0f);
//	}
//	if (m_Keyboard->KeyIsPressed(VK_RIGHT))	// right
//	{
//		//g_gfx->gameObject.AdjustPosition(0.05f * deltaTime, 0.0f, 0.0f);
//	}
//	if (m_Keyboard->KeyIsPressed(VK_UP))	// top
//	{
//		if (m_Keyboard->KeyIsPressed('Z'))
//		{
//			//g_gfx->gameObject.AdjustPosition(0.0f, 0.05f * deltaTime, 0.0f);
//		}
//		else
//		{
//			//g_gfx->gameObject.AdjustPosition(0.0f, 0.0f, 0.05f * deltaTime);
//		}
//	}
//	if (m_Keyboard->KeyIsPressed(VK_DOWN))	// bottom
//	{
//		if (m_Keyboard->KeyIsPressed('Z'))
//		{
//			//g_gfx->gameObject.AdjustPosition(0.0f, -0.05f * deltaTime, 0.0f);
//		}
//		else
//		{
//			//g_gfx->gameObject.AdjustPosition(0.0f, 0.0f, -0.05f * deltaTime);
//		}
//	}
//
//
//	//if (m_Keyboard->KeyIsPressedFirst('1'))
//	//{
//	//	g_Renderer->SetCameraNum();
//	//	m_CameraNum = g_Renderer->m_CameraNum;
//	//}
//
//	m_Keyboard->SetCurrentBeforeKey();
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
	//Keyboard Messages
	case WM_KEYDOWN:
	{
		unsigned char keycode = static_cast<unsigned char>(wParam);
		
		//m_spEngineBB->GetKeyInput()->
		//if (m_Keyboard->IsKeysAutoRepeat())
		//{
		//	m_Keyboard->OnKeyPressed(keycode);
		//}
		//else
		//{
		//	const bool wasPressed = lParam & 0x40000000;
		//	if (!wasPressed)
		//	{
		//		m_Keyboard->OnKeyPressed(keycode);
		//	}
		//}
		//return 0;
	}
	case WM_KEYUP:
	{
		unsigned char keycode = static_cast<unsigned char>(wParam);
		//m_Keyboard->OnKeyReleased(keycode);
		return 0;
	}
	case WM_CHAR:
	{
		unsigned char ch = static_cast<unsigned char>(wParam);
		//if (m_Keyboard->IsCharsAutoRepeat())
		//{
		//	m_Keyboard->OnChar(ch);
		//}
		//else
		//{
		//	const bool wasPressed = lParam & 0x40000000;
		//	if (!wasPressed)
		//	{
		//		m_Keyboard->OnChar(ch);
		//	}
		//}
		return 0;
	}
	//Mouse Messages
	case WM_MOUSEMOVE:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		//m_Mouse->OnMouseMove(x, y);
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		//m_Mouse->OnLeftPressed(x, y);
		return 0;
	}
	case WM_RBUTTONDOWN:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		//m_Mouse->OnRightPressed(x, y);
		return 0;
	}
	case WM_MBUTTONDOWN:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		//m_Mouse->OnMiddlePressed(x, y);
		return 0;
	}
	case WM_LBUTTONUP:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		//m_Mouse->OnLeftReleased(x, y);
		return 0;
	}
	case WM_RBUTTONUP:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		//m_Mouse->OnRightReleased(x, y);
		return 0;
	}
	case WM_MBUTTONUP:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		//m_Mouse->OnMiddleReleased(x, y);
		return 0;
	}
	case WM_MOUSEWHEEL:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
		{
			//m_Mouse->OnWheelUp(x, y);
		}
		else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
		{
			//m_Mouse->OnWheelDown(x, y);
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
