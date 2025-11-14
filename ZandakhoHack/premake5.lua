project "ZandakhoHack"
    kind "SharedLib"
    language "C++"
    cppdialect "C++23"
    staticruntime "off"

    buildoptions "/utf-8"

    targetdir ("%{wks.location}/Build/Binaries/" .. CONFIG.outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/Build/Intermediate/" .. CONFIG.outputdir .. "/%{prj.name}")

    pchheader "zhackpch.h"
    pchsource "Source/zhackpch.cpp"

    files
    {
        "Source/**.h",
        "Source/**.hpp", 
        "Source/**.cpp"
    }

    includedirs
    {
        "Source",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.MinHook}"
    }
    
    links
    {
        "ImGui",
        "MinHook"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
    }

    filter "kind:SharedLib"
        defines 
        {
            "ZH_BUILD_DLL"
        }

    filter "system:windows"
        systemversion "latest"
        defines "ZH_PLATFORM_WINDOWS"

        linkoptions
        {
            "/NODEFAULTLIB:LIBCMTD",
            "/NODEFAULTLIB:LIBCMT"
        }

        if USEAPI == GraphicsAPI.DirectX11 then
            links
            {
                "d3d11",
                "dxgi",
                "d3dcompiler"
            }
            defines
            {
                "USEAPI_DirectX11"
            }
        elseif USEAPI == GraphicsAPI.OpenGL then
            links
            {
                "opengl32"
            }
            defines
            {
                "USEAPI_OpenGL"
            }
        end

    filter "configurations:Debug"
        defines "ZH_DEBUG"
        runtime "Debug"
        symbols "on"

        linkoptions
        {
            "/NODEFAULTLIB:LIBCMT"
        }

    filter "configurations:Release"
        defines "ZH_RELEASE" 
        runtime "Release"
        optimize "on"

        linkoptions
        {
            "/NODEFAULTLIB:LIBCMTD"
        }
