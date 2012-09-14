#include "stdafx.h"
#include "D3D.h"

#include "Exception.h"

D3D::D3D() {
}


D3D::~D3D() {
}

void D3D::initialize(HWND hWnd, size_t width, size_t height) {
	DXGI_SWAP_CHAIN_DESC swdesc;			// swap chain description
	ZeroMemory(&swdesc, sizeof(swdesc));

	swdesc.BufferCount = 1;									// one back buffer i.e. only double buffering
	swdesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// 32-bit color
	swdesc.BufferDesc.Width = width;
	swdesc.BufferDesc.Height = height;
	swdesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swdesc.OutputWindow = hWnd;								// handle of window where we will draw
	swdesc.SampleDesc.Count = 1;							// multi sampling, 1 means off
	swdesc.Windowed = TRUE;									// windowed mode

	// create device and swap chain
	HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, 0, nullptr, 0,
						D3D11_SDK_VERSION, &swdesc, &swChain, &dev, nullptr, &devContext);
	if (FAILED(res))
		throw Win32Exception(res, true);

	// get back buffer
	ID3D11Texture2DPtr backBuffer;
	res = swChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	if (FAILED(res))
		throw Win32Exception(res, true);

	// create render target view
	res = dev->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
	if (FAILED(res))
		throw Win32Exception(res, true);

	// set render target
	devContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
}

void D3D::beginScene(const Color& bgColor) {
	float col[4] = { bgColor.r, bgColor.g, bgColor.b, 1.0f };
	devContext->ClearRenderTargetView(renderTargetView, col);
}

void D3D::endScene() {
	swChain->Present(0, 0);
}