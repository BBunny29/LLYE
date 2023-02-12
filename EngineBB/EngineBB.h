#pragma once
#include "EngineBBLibraryDefine.h"
#include "EngineBBDefine.h"
#include "Interface_EngineBB.h"
#include "Interface_ResourceManager.h"

class ComponentSystem;

/// <summary>
/// �ʿ��Ѱ� : 
/// 1. ������
/// 2. ������Ʈ �ý���
/// 3. ���ҽ� �Ŵ���
/// 4. Ÿ�̸�
/// 5. ���콺, Ű����
/// 6. �� �Ŵ���
/// </summary>

class EngineBB : public IEngineBB
{
public:
	EngineBB();
	~EngineBB();

	virtual bool Initialize(int hWND, int width, int height) override;
	virtual bool Loop() override;
	virtual void Finalize() override;

	/// OnResize
	virtual void OnResize(int width, int height) override;

	/// Input(keyboard / mouse)
	virtual void SetInput(std::shared_ptr<__interface IInput>& _input) override;
	virtual std::shared_ptr<__interface IInput> GetInput() override;

	/// Imgui �ڵ� ����
	virtual LRESULT ImGuiHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) override;

	///Getter
	virtual int GetScreenWidth() override;
	virtual int GetScreenHeight() override;
	virtual HWND GetHWND() override;

private:
	void UpdateAll(float dTime);
	void RenderAll();

private:
	std::shared_ptr<__interface IRenderer>			m_spDX11Renderer;
	std::shared_ptr<__interface IInput>				m_spInput;
	std::shared_ptr<__interface IResourceManager>	m_spResourceManager;

	std::shared_ptr<class ComponentSystem>			m_spComponentManager;
	
	HWND m_hWND;
	int m_width;
	int m_height;

};