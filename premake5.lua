include "./Vendors/Premake5/PremakeCustomization/SolutionItems.lua"
include "Dependencies.lua"
include "Config.lua"

workspace "ZandakhoHack"
    architecture(CONFIG.Architecture_x64)
    startproject(CONFIG.StartProject)

    configurations
    {
        "Debug",
        "Release"
    }

    flags
    {
        "MultiProcessorCompile"
    }

    SolutionItems
    {
        ".editorconfig"
    }

    group "Dependencies"
        include "Vendors/ImGui"
        include "Vendors/MinHook"
        include "Vendors/Premake5"
    group ""

    group "Core"
        include "ZandakhoHack"
    group ""