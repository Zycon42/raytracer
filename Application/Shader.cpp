#include "stdafx.h"

#include "Shader.h"

#include "File.h"
#include "Exception.h"

VertexShader::VertexShader(D3D* d3d, const char* file) : Shader(d3d) {
	File shaderFile(file, File::OpenMode::ReadOnly);
	auto shaderData = shaderFile.readAll();

	HRESULT hr = d3d->device()->CreateVertexShader(shaderData.data(), shaderData.size(), nullptr, &shader);
	if (FAILED(hr))
		throw Win32Exception("ID3D11Device::CreateVertexShader failed", true);
}

void VertexShader::use() {
	d3d->deviceContext()->VSSetShader(shader, nullptr, 0);
}

void VertexShader::setResource(UINT index, ID3D11ShaderResourceViewPtr view) {
	d3d->deviceContext()->VSSetShaderResources(index, 1, &view);
}

void VertexShader::setConstantBuffer(UINT index, ID3D11BufferPtr buff) {
	d3d->deviceContext()->VSSetConstantBuffers(index, 1, &buff);
}

void VertexShader::setSamplerState(UINT index, ID3D11SamplerStatePtr sampler) {
	d3d->deviceContext()->VSSetSamplers(index, 0, &sampler);
}

PixelShader::PixelShader(D3D* d3d, const char* file) : Shader(d3d) {
	File shaderFile(file, File::OpenMode::ReadOnly);
	auto shaderData = shaderFile.readAll();

	HRESULT hr = d3d->device()->CreatePixelShader(shaderData.data(), shaderData.size(), nullptr, &shader);
	if (FAILED(hr))
		throw Win32Exception("ID3D11Device::CreatePixelShader failed", true);
}

void PixelShader::use() {
	d3d->deviceContext()->PSSetShader(shader, nullptr, 0);
}

void PixelShader::setResource(UINT index, ID3D11ShaderResourceViewPtr view) {
	d3d->deviceContext()->PSSetShaderResources(index, 1, &view);
}

void PixelShader::setConstantBuffer(UINT index, ID3D11BufferPtr buff) {
	d3d->deviceContext()->PSSetConstantBuffers(index, 1, &buff);
}

void PixelShader::setSamplerState(UINT index, ID3D11SamplerStatePtr sampler) {
	d3d->deviceContext()->PSSetSamplers(index, 0, &sampler);
}