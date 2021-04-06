#include "Graphics.h"

Graphics::Graphics()
{
	m_device = NULL;
	m_deviceContext = NULL;

	m_dxgiDevice = NULL;
	m_dxgiAdapter = NULL;
	m_dxgiFactory = NULL;
	m_swapChain = NULL;

	m_renderTargetView = NULL;

	m_constantBuffer = NULL;

	m_inputLayout = NULL;

	m_indexBuffer = NULL;
	m_vertexShader = NULL;
	m_pixelShader = NULL;

	m_blob = NULL;
}

Graphics::~Graphics()
{
	if (m_device) m_device->Release();
	if (m_deviceContext) m_deviceContext->Release();

	if (m_dxgiDevice) m_dxgiDevice->Release();
	if (m_dxgiAdapter) m_dxgiAdapter->Release();
	if (m_dxgiFactory) m_dxgiFactory->Release();
	if (m_swapChain) m_swapChain->Release();

	if (m_renderTargetView) m_renderTargetView->Release();

	if (m_constantBuffer) m_constantBuffer->Release();

	if (m_indexBuffer) m_indexBuffer->Release();

	if (m_inputLayout) m_inputLayout->Release();

	if (m_vertexShader) m_vertexShader->Release();
	if (m_pixelShader) m_pixelShader->Release();

	if (m_blob) m_blob->Release();
}

void Graphics::Init()
{
	D3D_DRIVER_TYPE driverTypes[] = {
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_0
	};
	for (int i = 0; i < ARRAYSIZE(driverTypes); i++) {
		HRESULT r;
		r = D3D11CreateDevice(NULL, driverTypes[i], NULL, 0, featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &m_device, m_featureLevel, &m_deviceContext);
		if (r != NULL) break;
	}
}

void Graphics::InitSwapChain(HWND windowHandle, int width, int height)
{
	m_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgiDevice);
	m_dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgiAdapter);
	m_dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgiFactory);

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = windowHandle;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = true;

	m_dxgiFactory->CreateSwapChain(m_device, &swapChainDesc, &m_swapChain);

	ID3D11Texture2D *buffer;
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);
	m_device->CreateRenderTargetView(buffer, NULL, &m_renderTargetView);
	buffer->Release();
}

void Graphics::InitVertexBuffer(ID3D11Buffer **vertexBuffer, void* vertexList, int vertexSize, int listSize, void* shaderByteCode, int byteCodeSize)
{
	if (m_inputLayout) m_inputLayout->Release();

	m_vertexSize = vertexSize;

	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = vertexSize * listSize;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA subresourceData = { 0 };
	subresourceData.pSysMem = vertexList;

	m_device->CreateBuffer(&bufferDesc, &subresourceData, vertexBuffer);

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	m_device->CreateInputLayout(layout, ARRAYSIZE(layout), shaderByteCode, byteCodeSize, &m_inputLayout);
}

void Graphics::InitIndexBuffer(void* indexList, int listSize)
{
	if (m_indexBuffer) m_indexBuffer->Release();

	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = 4 * listSize;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA subresourceData = { 0 };
	subresourceData.pSysMem = indexList;

	m_device->CreateBuffer(&bufferDesc, &subresourceData, &m_indexBuffer);
}

void Graphics::InitConstantBuffer(void* buffer, int bufferSize)
{
	if (m_constantBuffer) m_constantBuffer->Release();

	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = bufferSize;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA subresourceData = { 0 };
	subresourceData.pSysMem = buffer;

	m_device->CreateBuffer(&bufferDesc, &subresourceData, &m_constantBuffer);
}

void Graphics::InitVertexShader(void* shaderByteCode, size_t byteCodeSize)
{
	m_device->CreateVertexShader(shaderByteCode, byteCodeSize, NULL, &m_vertexShader);
}

void Graphics::InitPixelShader(void* shaderByteCode, size_t byteCodeSize)
{
	m_device->CreatePixelShader(shaderByteCode, byteCodeSize, NULL, &m_pixelShader);
}

void Graphics::CompileVertexShader(const wchar_t* filename, const char* entryPointName, void** shaderByteCode, size_t *byteCodeSize)
{
	ID3DBlob *errorBlob = NULL;
	D3DCompileFromFile(filename, NULL, NULL, entryPointName, "vs_5_0", 0, 0, &m_blob, &errorBlob);

	*shaderByteCode = m_blob->GetBufferPointer();
	*byteCodeSize = m_blob->GetBufferSize();
}

void Graphics::CompilePixelShader(const wchar_t* filename, const char* entryPointName, void** shaderByteCode, size_t *byteCodeSize)
{
	ID3DBlob *errorBlob = NULL;
	D3DCompileFromFile(filename, NULL, NULL, entryPointName, "ps_5_0", 0, 0, &m_blob, &errorBlob);

	*shaderByteCode = m_blob->GetBufferPointer();
	*byteCodeSize = m_blob->GetBufferSize();
}

void Graphics::SetVertexBuffer(ID3D11Buffer *vertexBuffer)
{
	UINT stride = m_vertexSize;
	UINT offset = 0;
	m_deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	m_deviceContext->IASetInputLayout(m_inputLayout);
}

void Graphics::SetIndexBuffer()
{
	m_deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
}

void Graphics::SetConstantBuffer()
{
	m_deviceContext->VSSetConstantBuffers(0, 1, &m_constantBuffer);
	m_deviceContext->PSSetConstantBuffers(0, 1, &m_constantBuffer);
}

void Graphics::SetVertexShader()
{
	m_deviceContext->VSSetShader(m_vertexShader, NULL, 0);
}

void Graphics::SetPixelShader()
{
	m_deviceContext->PSSetShader(m_pixelShader, NULL, 0);
}

void Graphics::SetViewportSize(int width, int height)
{
	D3D11_VIEWPORT viewport = { 0 };
	viewport.Width = (float)width;
	viewport.Height = (float)height;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	m_deviceContext->RSSetViewports(1, &viewport);
}

void Graphics::SetTextureVS(ID3D11ShaderResourceView *shaderResourceView)
{
	m_deviceContext->VSSetShaderResources(0, 1, &shaderResourceView);
}

void Graphics::SetTexturePS(ID3D11ShaderResourceView *shaderResourceView)
{
	m_deviceContext->PSSetShaderResources(0, 1, &shaderResourceView);
}

void Graphics::ClearRenderTarget(float r, float g, float b, float a)
{
	float color[4] = { r, g, b, a };
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, NULL);
}

void Graphics::DrawTriangleList(int vertexCount, int startVertexIndex)
{
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_deviceContext->Draw(vertexCount, startVertexIndex);
}

void Graphics::DrawIndexedTriangleList(int indexCount, int startVertexIndex, int indexStartLocation)
{
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_deviceContext->DrawIndexed(indexCount, indexStartLocation, startVertexIndex);
}

void Graphics::DrawLineList(int vertexCount, int startVertexIndex)
{
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	m_deviceContext->Draw(vertexCount, startVertexIndex);
}

void Graphics::PresentSwapChain(bool vsync)
{
	m_swapChain->Present(vsync, 0);
}

void Graphics::UpdateConstantBuffer(void* buffer)
{
	m_deviceContext->UpdateSubresource(m_constantBuffer, NULL, NULL, buffer, NULL, NULL);
}

void Graphics::UpdateVertexBuffer(ID3D11Buffer **vertexBuffer, void* newVertexList, int listSize)
{
	D3D11_MAPPED_SUBRESOURCE resource = {};
	ZeroMemory(&resource, sizeof(D3D11_MAPPED_SUBRESOURCE));
	m_deviceContext->Map(*vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	memcpy(resource.pData, newVertexList, listSize);
	m_deviceContext->Unmap(*vertexBuffer, 0);
}

ID3D11Device *Graphics::GetDevice()
{
	return m_device;
}

ID3D11DeviceContext *Graphics::GetDeviceContext()
{
	return m_deviceContext;
}