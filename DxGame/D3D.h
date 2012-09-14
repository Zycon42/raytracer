#pragma once

#include "Canvas.h"

_COM_SMARTPTR_TYPEDEF(ID3D11Device, __uuidof(ID3D11Device));
_COM_SMARTPTR_TYPEDEF(IDXGISwapChain, __uuidof(IDXGISwapChain));
_COM_SMARTPTR_TYPEDEF(ID3D11DeviceContext, __uuidof(ID3D11DeviceContext));
_COM_SMARTPTR_TYPEDEF(ID3D11Texture2D, __uuidof(ID3D11Texture2D));
_COM_SMARTPTR_TYPEDEF(ID3D11RenderTargetView, __uuidof(ID3D11RenderTargetView));

class D3D
{
public:
	D3D();
	~D3D();

	void initialize(HWND hWnd, size_t width, size_t height);

	void beginScene(const Color& bgColor);
	void endScene();

	ID3D11DevicePtr device() { return dev; }
	IDXGISwapChainPtr swapChain() { return swChain; }
	ID3D11DeviceContextPtr deviceContext() { return devContext; }
private:
	ID3D11DevicePtr dev;
	IDXGISwapChainPtr swChain;
	ID3D11DeviceContextPtr devContext;
	ID3D11RenderTargetViewPtr renderTargetView;
};

