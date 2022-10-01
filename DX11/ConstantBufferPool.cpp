#include "pch.h"
#include "ConstantBufferPool.h"

#include "COMException.h"

ConstantBuffer<CB_VS_WVP>* ConstantBufferPool::m_vs_WVPMatrix = nullptr;

ConstantBuffer<CB_VS_1M>* ConstantBufferPool::m_vs_1Matrix = nullptr;
ConstantBuffer<CB_VS_2M>* ConstantBufferPool::m_vs_2Matrix = nullptr;
ConstantBuffer<CB_VS_3M>* ConstantBufferPool::m_vs_3Matrix = nullptr;


void ConstantBufferPool::Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
{
	m_vs_WVPMatrix = new ConstantBuffer<CB_VS_WVP>();

	m_vs_1Matrix = new ConstantBuffer<CB_VS_1M>();
	m_vs_2Matrix = new ConstantBuffer<CB_VS_2M>();
	m_vs_3Matrix = new ConstantBuffer<CB_VS_3M>();

	try
	{
		HRESULT hr;

		// 쉐이더 상수버퍼 초기화
		{
			hr = m_vs_WVPMatrix->Initialize(pDevice, pDeviceContext);
			THROW_COM_ERROR_IF_FAILED(hr, "Create Object Per ConstantBuffer Fail");
		}

		{
			hr = m_vs_1Matrix->Initialize(pDevice, pDeviceContext);
			THROW_COM_ERROR_IF_FAILED(hr, "Create Object Per ConstantBuffer 'm_vs_1Matrix' Fail");
		}

		{
			hr = m_vs_2Matrix->Initialize(pDevice, pDeviceContext);
			THROW_COM_ERROR_IF_FAILED(hr, "Create Object Per ConstantBuffer 'm_vs_2Matrix' Fail");
		}

		{
			hr = m_vs_3Matrix->Initialize(pDevice, pDeviceContext);
			THROW_COM_ERROR_IF_FAILED(hr, "Create Object Per ConstantBuffer 'm_vs_3Matrix' Fail");
		}

	}
	catch (COMException& exception)
	{
		ErrorLogger::Log(exception);
	}
}

ConstantBuffer<CB_VS_WVP>* ConstantBufferPool::GetWVPMatrix()
{
	return m_vs_WVPMatrix;
}

ConstantBuffer<CB_VS_1M>* ConstantBufferPool::Get1Matrix()
{
	return m_vs_1Matrix;
}

ConstantBuffer<CB_VS_2M>* ConstantBufferPool::Get2Matrix()
{
	return m_vs_2Matrix;
}

ConstantBuffer<CB_VS_3M>* ConstantBufferPool::Get3Matrix()
{
	return m_vs_3Matrix;
}
