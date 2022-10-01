#include "pch.h"
#include "Box.h"

bool Box::Initialize(ID3D11Device* device, 
	ID3D11DeviceContext* deviceContext, 
	ID3D11ShaderResourceView* texture, 
	ConstantBuffer<CB_VS_2M>& cb_vs_vertexshader)
{
	this->m_cpDevice = device;
	this->m_cpDeviceContext = deviceContext;
	this->texture = texture;
	this->cb_vs_vertexshader = &cb_vs_vertexshader;

	try
	{
		//Textured Square
		Vertex::VertexPosNormalTex v[] =
		{
			//FRONT
			Vertex::VertexPosNormalTex(-0.5f, -0.5f, -0.5f,		0.f, 0.f, 0.f,		0.0f, 1.0f),  //Bottom left		[0]
			Vertex::VertexPosNormalTex(-0.5f,  0.5f, -0.5f,		0.f, 0.f, 0.f,		0.0f, 0.0f),  //Top left			[1]	
			Vertex::VertexPosNormalTex(0.5f,  0.5f, -0.5f,		0.f, 0.f, 0.f,		1.0f, 0.0f),  //Top right		[2]
			Vertex::VertexPosNormalTex(0.5f, -0.5f, -0.5f,		0.f, 0.f, 0.f,		1.0f, 1.0f),  //Bottom right		[3]

			//BACK
			Vertex::VertexPosNormalTex(-0.5f, -0.5f, 0.5f,		0.f, 0.f, 0.f,		0.0f, 1.0f),  //Bottom left		[4]
			Vertex::VertexPosNormalTex(-0.5f,  0.5f, 0.5f,		0.f, 0.f, 0.f,		0.0f, 0.0f),  //Top left			[5]
			Vertex::VertexPosNormalTex(0.5f,  0.5f, 0.5f,		0.f, 0.f, 0.f,		1.0f, 0.0f),  //Top right		[6]
			Vertex::VertexPosNormalTex(0.5f, -0.5f, 0.5f,		0.f, 0.f, 0.f,		1.0f, 1.0f),  //Bottom right		[7]
		};

		//버텍스 버퍼 불러오기
		HRESULT hr = this->vertexBuffer.Initialize(this->m_cpDevice.Get(), v, ARRAYSIZE(v));
		THROW_COM_ERROR_IF_FAILED(hr, "버텍스 버퍼를 생성하는데 실패했습니다");

		DWORD indices[] =
		{
			//FRONT
			0, 1, 2,
			0, 2, 3,
			//BACK
			7, 6, 5,
			7, 5, 4,
			//RIGHT
			3, 2, 6,
			3, 6, 7,
			//LEFT
			4, 5, 1,
			4, 1, 0,
			//TOP
			1, 5, 6,
			1, 6, 2,
			//BOTTOM
			4, 0, 3,
			4, 3, 7
		};

		//Index Data 불러오기
		hr = this->indexBuffer.Initialize(this->m_cpDevice.Get(), indices, ARRAYSIZE(indices));
		THROW_COM_ERROR_IF_FAILED(hr, "Failed to initialize index buffer.");
	}
	catch (COMException& exception)
	{
		ErrorLogger::Log(exception);
		return false;
	}

	return true;
}

void Box::Draw(const XMMATRIX& worldMatrix, const XMMATRIX& viewProjectionMatrix)
{
	//Constant buffer 와 WVP Matrix 업데이트
	this->cb_vs_vertexshader->data.matrix1 = worldMatrix * viewProjectionMatrix; //Calculate World-View-Projection Matrix
	this->cb_vs_vertexshader->ApplyChanges();
	this->m_cpDeviceContext->VSSetConstantBuffers(0, 1, this->cb_vs_vertexshader->GetAddressOf());

	this->m_cpDeviceContext->PSSetShaderResources(0, 1, &this->texture); //Set Texture
	UINT offset = 0;
	this->m_cpDeviceContext->IASetVertexBuffers(0, 1, this->vertexBuffer.GetAddressOf(), this->vertexBuffer.StridePtr(), &offset);
	this->m_cpDeviceContext->IASetIndexBuffer(this->indexBuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
	this->m_cpDeviceContext->DrawIndexed(this->indexBuffer.IndexCount(), 0, 0); //Draw
}
