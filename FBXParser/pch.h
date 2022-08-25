// FBXParser의 pch.h

#ifndef PCH_H
#define PCH_H

#define WIN32_LEAN_AND_MEAN   

#include <windows.h>
#include <memory>
#include <iostream>

/// STL
#include <vector>
#include <string>

/// Assist Lib 헤더
#include "DebugString.h"
#include "ErrorLogger.h"
#include "COMException.h"
#include "PathFinder.h"
#include "FileNameReader.h"
#include "StringHelper.h"
#include "Stopwatch.h"

// nullpointer 체크
#define ASSERT_NULLCHECK(pointer, message)	DebugString::PDS("Null Pointer : %s", message); \
											DebugString::PDS_LOG; \
											assert(pointer != nullptr && message); 		

#endif //PCH_H
