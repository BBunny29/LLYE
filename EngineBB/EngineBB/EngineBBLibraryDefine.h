#pragma once

// Engine
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