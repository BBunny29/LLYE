#pragma once
#include "EngineBBLibraryDefine.h"
#include "EngineBBDefine.h"
#include "IEngineBB.h"
#include <memory>

__interface IRenderer;

class DLLImporter;

class EngineBB : public IEngineBB
{
public:
	EngineBB();
	~EngineBB();

	virtual HRESULT Init() override;

	virtual int testFunc(int i) override;

private:
	//virtual std::shared_ptr<IRenderer> CreateRenderer(const wchar_t* dllPath) override;

private:

	std::shared_ptr<DLLImporter> m_spDLLImporter;
	std::shared_ptr<IRenderer> m_spDX11Renderer;

	//Timer* m_timer;
	//KeyboardClass* m_keyboard;
	//MouseClass* m_mouse;

};