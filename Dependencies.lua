IncludeDir = {}
IncludeDir["ImGui"] = "%{wks.location}/Vendors/ImGui"
IncludeDir["MinHook"] = "%{wks.location}/Vendors/MinHook/include"

Library = {}

-- Windows SDK
Library["d3d11"] = "d3d11.lib"
Library["d3dcompiler"] = "d3dcompiler.lib"
Library["dxgi"] = "dxgi.lib"

-- MinHook
Library["MinHook"] = "MinHook.lib"