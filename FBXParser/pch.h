// pch.h: �̸� �����ϵ� ��� �����Դϴ�.
// �Ʒ� ������ ������ �� ���� �����ϵǾ�����, ���� ���忡 ���� ���� ������ ����մϴ�.
// �ڵ� ������ �� ���� �ڵ� �˻� ����� �����Ͽ� IntelliSense ���ɿ��� ������ ��Ĩ�ϴ�.
// �׷��� ���⿡ ������ ������ ���� �� ������Ʈ�Ǵ� ��� ��� �ٽ� �����ϵ˴ϴ�.
// ���⿡ ���� ������Ʈ�� ������ �߰����� ������. �׷��� ������ ���ϵ˴ϴ�.

#ifndef PCH_H
#define PCH_H

#define WIN32_LEAN_AND_MEAN   

#include <windows.h>
#include <memory>

#include <iostream>
#include <string>
#include <string>

// Assist Lib
#include "DebugString.h"
#include "ErrorLogger.h"
#include "COMException.h"
#include "PathFinder.h"
#include "FileNameReader.h"
#include "StringHelper.h"
#include "Timer.h"

// nullpointer üũ
#define ASSERT_NULLCHECK(pointer, message)	DebugString::PDS("Null Pointer : %s", message); \
											DebugString::PDS_LOG; \
											assert(pointer != nullptr && message); 		

#endif //PCH_H
