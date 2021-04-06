#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>

class Graphics
{
public:
	Graphics();
	~Graphics();

public:
	void Init();

	void InitSwapChain(HWND windowHandle, int width, int height);

	void InitVertexBuffer(ID3D11Buffer **vertexBuffer, void* vertexList, int vertexSize, int listSize, void* shaderByteCode, int byteCodeSize);
	void InitIndexBuffer(void* indexList, int listSize);

	void InitConstantBuffer(void* buffer, int bufferSize);

	void InitVertexShader(void* shaderByteCode, size_t byteCodeSize);
	void InitPixelShader(void* shaderByteCode, size_t byteCodeSize);

public:
	void CompileVertexShader(const wchar_t* filename, const char* entryPointName, void** shaderByteCode, size_t *byteCodeSize);
	void CompilePixelShader(const wchar_t* filename, const char* entryPointName, void** shaderByteCode, size_t *byteCodeSize);

public:
	void SetViewportSize(int width, int height);
	void SetVertexBuffer(ID3D11Buffer *vertexBuffer);
	void SetIndexBuffer();
	void SetConstantBuffer();
	void SetVertexShader();
	void SetPixelShader();
	void SetTextureVS(ID3D11ShaderResourceView *shaderResourceView);
	void SetTexturePS(ID3D11ShaderResourceView *shaderResourceView);

public:
	void ClearRenderTarget(float r, float g, float b, float a);
	
	void DrawTriangleList(int vertexCount, int startVertexIndex);
	void DrawIndexedTriangleList(int indexCount, int startVertexIndex, int indexStartLocation);
	void DrawLineList(int vertexCount, int startVertexIndex);

	void PresentSwapChain(bool vsync);
	void UpdateConstantBuffer(void* buffer);
	void UpdateVertexBuffer(ID3D11Buffer **vertexBuffer, void* newVertexList, int listSize);

public:
	ID3D11Device *GetDevice();
	ID3D11DeviceContext *GetDeviceContext();

private:
	ID3D11Device *m_device;
	ID3D11DeviceContext *m_deviceContext;
	D3D_FEATURE_LEVEL *m_featureLevel;

	IDXGIDevice *m_dxgiDevice;
	IDXGIAdapter *m_dxgiAdapter;
	IDXGIFactory *m_dxgiFactory;
	IDXGISwapChain *m_swapChain;

	ID3D11RenderTargetView *m_renderTargetView;

	ID3D11Buffer *m_constantBuffer;

	ID3D11Buffer *m_indexBuffer;

	int m_vertexSize;

	ID3D11InputLayout *m_inputLayout;

	ID3DBlob *m_blob;
	ID3D11VertexShader *m_vertexShader;
	ID3D11PixelShader *m_pixelShader;
};