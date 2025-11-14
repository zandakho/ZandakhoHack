#ifndef __HOOK_H__
#define __HOOK_H__

#include <stdint.h>

#define HOOK_VERSION "1.2.6"

#define HOOK_INCLUDE_D3D9   0 // 1 if you need D3D9 hook
#define HOOK_INCLUDE_D3D10  0 // 1 if you need D3D10 hook
#define HOOK_INCLUDE_D3D11  0 // 1 if you need D3D11 hook
#define HOOK_INCLUDE_D3D12  0 // 1 if you need D3D12 hook
#define HOOK_INCLUDE_OPENGL 1 // 1 if you need OpenGL hook
#define HOOK_INCLUDE_VULKAN 0 // 1 if you need Vulkan hook
#define HOOK_USE_MINHOOK    1 // 1 if you will use Hook::Bind function

#define HOOK_ARCH_X64 0
#define HOOK_ARCH_X86 0

#if defined(_M_X64)	
# undef  HOOK_ARCH_X64
# define HOOK_ARCH_X64 1
#else
# undef  HOOK_ARCH_X86
# define HOOK_ARCH_X86 1
#endif

#if HOOK_ARCH_X64
typedef uint64_t uint150_t;
#else
typedef uint32_t uint150_t;
#endif

namespace Hook
{
	struct Status
	{
		enum Enum
		{
			UnknownError = -1,
			NotSupportedError = -2,
			ModuleNotFoundError = -3,

			AlreadyInitializedError = -4,
			NotInitializedError = -5,

			Success = 0,
		};
	};

	struct RenderType
	{
		enum Enum
		{
			None,

			D3D9,
			D3D10,
			D3D11,
			D3D12,

			OpenGL,
			Vulkan,

			Auto
		};
	};

	Status::Enum Init(RenderType::Enum renderType);
	void Shutdown();

	Status::Enum Bind(uint16_t index, void** original, void* function);
	void Unbind(uint16_t index);

	RenderType::Enum GetRenderType();
	uint150_t* GetMethodsTable();
}

#endif
