project "ZandakhoHack"
    kind "SharedLib"
    language "C++"
    cppdialect "C++23"
    staticruntime "off"

    buildoptions "/utf-8"

    targetdir ("%{wks.location}/Build/Binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/Build/Intermediate/" .. outputdir .. "/%{prj.name}")

    files
    {
        "Source/**.h",
        "Source/**.hpp",
        "Source/**.cpp"
    }

    includedirs
    {
        "Source",
        "%{IncludeDir.ImGui}"
    }

    links
    {
        "ImGui"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines "ZH_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "ZH_RELEASE"
        runtime "Release"
        optimize "on"
