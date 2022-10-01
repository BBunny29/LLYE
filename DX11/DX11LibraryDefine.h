#pragma once

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "dxguid.lib")

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