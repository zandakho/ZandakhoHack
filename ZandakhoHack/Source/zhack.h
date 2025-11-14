#pragma once

#if defined(USEAPI_DirectX11)
	#include <d3d11.h>
	#include <dxgi.h>
#endif

#include "MinHook/Hook.h"
#include "imgui.h"

#if defined(USEAPI_OpenGL)
	#include "backends/imgui_impl_opengl3.h"

	#include <gl/GL.h>
#endif

#if defined(USEAPI_DirectX11)
	#include "backends/imgui_impl_dx11.h"
#endif

#include "backends/imgui_impl_win32.h"

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;

