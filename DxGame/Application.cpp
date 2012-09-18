#include "stdafx.h"
#include "Application.h"

#include "Exception.h"
#include "Scene.h"
#include "Surface.h"
#include "Renderer.h"
#include "Shader.h"

LPCTSTR Application::CLASS_NAME = TEXT("DxGame");
LPCTSTR Application::WND_TITLE = TEXT("Test");

Application::Application(HINSTANCE hInstance) : hInstance(hInstance), window(hInstance, CLASS_NAME) {
}

int Application::run() {
	init(640, 480);

	MSG msg;
	for (;;) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			renderFrame();
		}
	}
	return msg.wParam;
}

void Application::init(int width, int height) {
	window.setSize(width, height);
	window.create(WND_TITLE);

	d3d.initialize(window.handle(), width, height);

	auto scene = std::make_shared<Scene>();
	auto surface = std::make_shared<Surface>(width, height);
	Renderer renderer(scene, surface);
	renderer.render();

	std::unique_ptr<uint8_t[]> data(new uint8_t[surface->width() * surface->height() * 4]);
	surface->storePixels(data.get());

	// texture
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = static_cast<UINT>(surface->width());
	desc.Height = static_cast<UINT>(surface->height());
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = data.get();
	initData.SysMemPitch = static_cast<UINT>(surface->width() * 4);
	initData.SysMemSlicePitch = 0;

	ID3D11Texture2DPtr tex;
	HRESULT hr = d3d.device()->CreateTexture2D(&desc, &initData, &tex);
	if (FAILED(hr))
		throw Win32Exception("ID3D11Device::CreateTexture2D failed", true);

	// shader resource view
	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
	ZeroMemory(&SRVDesc, sizeof(SRVDesc));
	SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = 1;
	ID3D11ShaderResourceViewPtr shaderTexture;
	hr = d3d.device()->CreateShaderResourceView(tex, &SRVDesc, &shaderTexture);
	if (FAILED(hr))
		throw Win32Exception("ID3D11Device::CreateShaderResourceView failed", true);

	// sampler
	D3D11_SAMPLER_DESC SampDesc;
	ZeroMemory(&SampDesc, sizeof(SampDesc));
	SampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	SampDesc.MaxAnisotropy = 1;
	SampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	SampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	ID3D11SamplerStatePtr sampler;
	hr = d3d.device()->CreateSamplerState(&SampDesc, &sampler);
	if (FAILED(hr))
		throw Win32Exception("ID3D11Device::CreateSamplerState failed", true);

	// vertex shader setup
	auto vertexShader = d3d.createVertexShader("VertexShader.cso");
	vertexShader->use();

	// pixel shader setup
	auto pixelShader = d3d.createPixelShader("TexturePixelShader.cso");
	pixelShader->setResource(0, shaderTexture);
	pixelShader->setSamplerState(0, sampler);
	pixelShader->use();
}

void Application::renderFrame() {
	d3d.beginScene(Color::black());

	d3d.endScene();
}