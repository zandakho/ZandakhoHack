#include"zhackpch.h"

#include <misc/cpp/imgui_stdlib.cpp>

#if defined(USEAPI_OpenGL)
	#include "backends/imgui_impl_opengl3.cpp"
#endif

#if defined(USEAPI_DirectX11)
	#include "backends/imgui_impl_dx11.cpp"
#endif

#include "backends/imgui_impl_win32.cpp"
