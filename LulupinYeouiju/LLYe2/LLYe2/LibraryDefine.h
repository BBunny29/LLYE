#pragma once

// Engine
#ifdef _WIN64
#ifdef _DEBUG
#pragma comment(lib, "EngineBB_64DEBUG")
#else
#pragma comment(lib, "EngineBB_64")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib, "EngineBB_32DEBUG")
#else
#pragma comment(lib, "EngineBB_32")
#endif
#endif