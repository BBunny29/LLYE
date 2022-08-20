#pragma once
#include "EngineBBLibraryDefine.h"
#include "EngineBBDefine.h"
#include "ITest.h"

/// <summary>
/// �ʿ��Ѱ� : 
/// 1. ������Ʈ �ý���
/// 2. Ÿ�̸�
/// 3. ���콺, Ű����
/// 4. 
/// </summary>

class Test : public ITest
{
public:
	Test();
	~Test();

	virtual HRESULT Initialize(int hWND, int width, int height) override;

private:
	std::shared_ptr<__interface IRenderer> m_spDX11Renderer;

	//Timer* m_timer;
	//KeyboardClass* m_keyboard;
	//MouseClass* m_mouse;

};