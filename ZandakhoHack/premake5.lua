project "ZandakhoHack"
    kind "SharedLib"
    language "C++"
    cppdialect "C++23"
    staticruntime "off"

    buildoptions "/utf-8"

    targetdir ("%{wks.location}/Build/Binaries/" .. CONFIG.outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/Build/Intermediate/" .. CONFIG.outputdir .. "/%{prj.name}")

    files
    {
        "Source/**.h",
        "Source/**.hpp", 
        "Source/**.cpp",
        "Source/**.rc",
        "Source/**.def"
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
        "MinHook",
        "%{Library.d3d11}",
        "%{Library.d3dcompiler}",
        "%{Library.dxgi}"
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
