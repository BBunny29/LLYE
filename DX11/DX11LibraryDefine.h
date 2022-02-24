#pragma once

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "D3DCompiler.lib")

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
