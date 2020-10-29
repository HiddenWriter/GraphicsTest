#pragma once
class Graphics
{
public:
	Graphics(HWND _hwnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics();

	void EndFrame();
	
	// Test Code //
	void ClearBuffer(float _r, float _g, float _b)
	{
		const float colour[] = { _r, _g, _b, 1.0f };
		mpContext->ClearRenderTargetView(mpTarget.Get(), colour);
		return;
	}
private:
	
	Microsoft::WRL::ComPtr<ID3D11Device> mpDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> mpSwap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> mpContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mpTarget;

};

