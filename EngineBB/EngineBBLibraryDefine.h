#pragma once

// DX11
#ifdef _WIN64
#ifdef _DEBUG
#pragma comment(lib, "DX11_x64Debug.lib")
#else
#pragma comment(lib, "DX11_x64Release.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib, "DX11_x86Debug.lib")
#else
#pragma comment(lib, "DX11_x86Release.lib")
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

// ResourceManager
#ifdef _WIN64
#ifdef _DEBUG
#pragma comment(lib, "ResourceManager_x64Debug.lib")
#else
#pragma comment(lib, "ResourceManager_x64Release.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib, "ResourceManager_x86Debug.lib")
#else
#pragma comment(lib, "ResourceManager_x86Release.lib")
#endif
#endif