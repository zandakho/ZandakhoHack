#include "ZandakhoHack.h"

#include <d3d11.h>
#include <imgui.h>
#include <backends/imgui_impl_dx11.h>
#include <backends/imgui_impl_win32.h>

#include <MinHook.h>

#include <print>
#include <cstdio>
#include <string>

#ifdef ZH_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

ID3D11Device* g_pd3dDevice = nullptr;
ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
IDXGISwapChain* g_pSwapChain = nullptr;
ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;
HWND g_hWindow = nullptr;
WNDPROC oWndProc = nullptr;

bool CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool InitializeImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui::StyleColorsDark();

	if (!ImGui_ImplWin32_Init(g_hWindow))
	{
		return false;
	}

	if (!ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext))
	{
		return false;
	}

	return true;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

extern "C" ZH_API bool InitializeHack()
{
	g_hWindow = FindWindowA(nullptr, "Target Game Window");

	if (!g_hWindow)
	{
		g_hWindow = FindWindowA("UnityWndClass", nullptr);
	}

	if (g_hWindow)
	{
		oWndProc = (WNDPROC)SetWindowLongPtr(g_hWindow, GWLP_WNDPROC, (LONG_PTR)WndProc);
		return InitializeImGui();
	}

	return false;
}

extern "C" ZH_API void ShutdownHack()
{
	if (g_hWindow && oWndProc)
	{
		SetWindowLongPtr(g_hWindow, GWLP_WNDPROC, (LONG_PTR)oWndProc);
	}

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	CleanupRenderTarget();
	if (g_pSwapChain)
	{
		g_pSwapChain->Release();
		g_pSwapChain = nullptr;
	}

	if (g_pd3dDeviceContext)
	{
		g_pd3dDeviceContext->Release();
		g_pd3dDeviceContext = nullptr;
	}

	if (g_pd3dDevice)
	{
		g_pd3dDevice->Release();
		g_pd3dDevice = nullptr;
	}
}

bool CreateRenderTarget()
{
	if (!g_pSwapChain || !g_pd3dDevice) return false;

	ID3D11Texture2D* pBackBuffer;
	g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
	if (!pBackBuffer) return false;

	g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
	pBackBuffer->Release();
	return true;
}

void CleanupRenderTarget()
{
	if (g_mainRenderTargetView)
	{
		g_mainRenderTargetView->Release();
		g_mainRenderTargetView = nullptr;
	}
}

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, msg, wParam, lParam);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		CreateThread(nullptr, 0, [](LPVOID param) -> DWORD
			{
				InitializeHack();
				return 0;
			},
			nullptr, 0, nullptr);
	}
	else if (reason == DLL_PROCESS_DETACH)
	{
		ShutdownHack();
	}
	return TRUE;
}
