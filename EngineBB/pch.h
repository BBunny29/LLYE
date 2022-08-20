// EngineBB의 pch.h

#ifndef PCH_H
#define PCH_H

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#include <Windows.h>
#include <vector>

#include "EngineBBDefine.h"
#include "EngineBBdllDefine.h"
#include "EngineBBLibraryDefine.h"

/// Assist Lib 헤더
#include "DllLoader.h"
#include "DebugString.h"
#include "ErrorLogger.h"
#include "COMException.h"
#include "PathFinder.h"
#include "FileNameReader.h"
#include "StringHelper.h"
#include "Timer.h"

// nullpointer 체크
#define ASSERT_NULLCHECK(pointer, message)	DebugString::PDS("Null Pointer : %s", message); \
											DebugString::PDS_LOG; \
											assert(pointer != nullptr && message); 	

#endif //PCH_H
