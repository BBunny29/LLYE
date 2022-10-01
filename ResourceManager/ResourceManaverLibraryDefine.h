#pragma once

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "D3DCompiler.lib")

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