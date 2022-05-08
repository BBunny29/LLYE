#pragma once

// EngineBB
#ifdef _WIN64
#ifdef _DEBUG
#pragma comment(lib, "EngineBB_x64Debug.lib")
#else
#pragma comment(lib, "EngineBB_x64Release.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib, "EngineBB_x86Debug.lib")
#else
#pragma comment(lib, "EngineBB_x86Release.lib")
#endif
#endif

// Assistance
#ifdef _WIN64
#ifdef _DEBUG
#pragma comment(lib, "Assistance_x64Debug.lib")
#else
#pragma comment(lib, "Assistance_x64Release.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib, "Assistance_x86Debug.lib")
#else
#pragma comment(lib, "Assistance_x86Release.lib")
#endif
#endif