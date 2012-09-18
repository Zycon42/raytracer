#pragma once

#include "D3D.h"

class Shader
{
public:
	virtual ~Shader() { }

	virtual void use() = 0;
	virtual void setResource(UINT index, ID3D11ShaderResourceViewPtr view) = 0;
	virtual void setConstantBuffer(UINT index, ID3D11BufferPtr buff) = 0;
	virtual void setSamplerState(UINT index, ID3D11SamplerStatePtr sampler) = 0;
protected:
	Shader(D3D* d3d) : d3d(d3d) { }
	D3D* d3d;
};

class VertexShader : public Shader
{
public:
	VertexShader(D3D* d3d, const char* file);

	virtual void use() override;
	virtual void setResource(UINT index, ID3D11ShaderResourceViewPtr view) override;
	virtual void setConstantBuffer(UINT index, ID3D11BufferPtr buff) override;
	virtual void setSamplerState(UINT index, ID3D11SamplerStatePtr sampler) override;
private:
	ID3D11VertexShaderPtr shader;
};

class PixelShader : public Shader
{
public:
	PixelShader(D3D* d3d, const char* file);

	virtual void use() override;
	virtual void setResource(UINT index, ID3D11ShaderResourceViewPtr view) override;
	virtual void setConstantBuffer(UINT index, ID3D11BufferPtr buff) override;
	virtual void setSamplerState(UINT index, ID3D11SamplerStatePtr sampler) override;
private:
	ID3D11PixelShaderPtr shader;
};