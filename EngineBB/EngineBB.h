#pragma once
#include "EngineBBLibraryDefine.h"
#include "EngineBBDefine.h"
#include "Interface_EngineBB.h"

/// <summary>
/// 필요한것 : 
/// 1. 컴포넌트 시스템
/// 2. 타이머
/// 3. 마우스, 키보드
/// </summary>

class EngineBB : public IEngineBB
{
public:
	EngineBB();
	~EngineBB();

	virtual bool Initialize(int hWND, int width, int height) override;
	virtual bool Loop() override;
	virtual void Finalize() override;

	/// Input(keyboard / mouse)
	virtual void SetInput(std::shared_ptr<__interface IInput>& _input) override;
	virtual std::shared_ptr<__interface IInput> GetInput() override;

	/// Imgui 핸들 셋팅
	virtual LRESULT ImGuiHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) override;

private:
	void RenderAll();

private:
	std::shared_ptr<__interface IRenderer> m_spDX11Renderer;
	std::shared_ptr<__interface IInput> m_spInput;

};