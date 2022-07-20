#pragma once
#include "pch.h"

// FBX SDK
#ifdef _WIN64
#ifdef _DEBUG
#pragma comment(lib, "libfbxsdk_x64d.lib")
#else
#pragma comment(lib, "libfbxsdk_x64.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib, "libfbxsdk_x32d.lib")
#else
#pragma comment(lib, "libfbxsdk_x32.lib")
#endif
#endif

// DXTK
#ifdef _WIN64
#ifdef _DEBUG
#pragma comment(lib, "DirectXTK_x64d.lib")
#else
#pragma comment(lib, "DirectXTK_x64.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib, "DirectXTK_x32d.lib")
#else
#pragma comment(lib, "DirectXTK_x32.lib")
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