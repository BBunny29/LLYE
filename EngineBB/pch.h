// EngineBB의 pch.h

#ifndef PCH_H
#define PCH_H

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#include <Windows.h>

/// STL
#include <vector>
#include <string>

#include "EngineBBDefine.h"			// 헤더들
#include "EngineBBdllDefine.h"		// 라이브러리의 이름 설정
#include "EngineBBLibraryDefine.h"	// 이 라이브러리에 연결하는 라이브러리들


// nullpointer 체크
#define ASSERT_NULLCHECK(pointer, message)	DebugString::PDS("Null Pointer : %s", message); \
											DebugString::PDS_LOG; \
											assert(pointer != nullptr && message); 	

#endif //PCH_H
