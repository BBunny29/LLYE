#pragma once

#include "VertexHelper.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

class Box
{
public:
	bool Initialize(ID3D11Device* device, 
		ID3D11DeviceContext* deviceContext, 
		ID3D11ShaderResourceView* texture, 
		ConstantBuffer<CB_VS_2M>& cb_vs_vertexshader);

	void Draw(const XMMATRIX& worldMatrix, 
		const XMMATRIX& viewProjectionMatrix);

private:
	Microsoft::WRL::ComPtr<ID3D11Device> m_cpDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_cpDeviceContext;

	ConstantBuffer<CB_VS_2M>* cb_vs_vertexshader = nullptr;
	ID3D11ShaderResourceView* texture = nullptr;

	VertexBuffer<Vertex::VertexPosNormalTex> vertexBuffer;
	IndexBuffer indexBuffer;
};

