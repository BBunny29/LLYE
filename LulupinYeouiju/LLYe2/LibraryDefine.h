#pragma once

// EngineBB
#ifdef _WIN64
#ifdef _DEBUG
#pragma comment(lib, "EngineBB_x64Debug")
#else
#pragma comment(lib, "EngineBB_x64Release")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib, "EngineBB_x86Debug")
#else
#pragma comment(lib, "EngineBB_x86Release")
#endif
#endif

// Debugger
#ifdef _WIN64
#ifdef _DEBUG
#pragma comment(lib, "Debugger_x64Debug")
#else
#pragma comment(lib, "Debugger_x64Release")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib, "Debugger_x86Debug")
#else
#pragma comment(lib, "Debugger_x86Release")
#endif
#endif