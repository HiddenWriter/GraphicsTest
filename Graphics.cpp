#include "pch.h"
#include "Graphics.h"

Graphics::Graphics(HWND _hwnd)
{

	DXGI_SWAP_CHAIN_DESC sd = {};
	{
		sd.BufferDesc.Width = 0;
		sd.BufferDesc.Height = 0;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 0;
		sd.BufferDesc.RefreshRate.Denominator = 0;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;
		sd.OutputWindow = _hwnd;
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		sd.Flags = 0;
	}
	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&mpSwap,
		&mpDevice,
		nullptr,
		&mpContext
	);

	Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer;
	mpSwap->GetBuffer(0, __uuidof(ID3D11Resource), (&pBackBuffer));
	mpDevice->CreateRenderTargetView(
		pBackBuffer.Get(),
		nullptr,
		&mpTarget
	);

	return;
}

Graphics::~Graphics()
{
	return;
}

void Graphics::EndFrame()
{
	mpSwap->Present(1u, 0u);

	return;
}
