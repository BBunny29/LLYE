#pragma once

#pragma comment(lib, "d3d11")
#pragma comment(lib, "DXGI")
#pragma comment(lib, "D3DCompiler")

// Engine
#ifdef _WIN64
#ifdef _DEBUG
#pragma comment(lib, "JJEngine64DEBUG")
#else
#pragma comment(lib, "JJEngine64")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib, "JJEngineDEBUG")
#else
#pragma comment(lib, "JJEngine")
#endif
#endif


