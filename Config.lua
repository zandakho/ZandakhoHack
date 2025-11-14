CONFIG = 
{
    StartProject = "ZandakhoHack",
    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}",

    Architecture_x64 = "x64",
    Architecture_x86 = "x86",
}

GraphicsAPI = 
{
    DirectX11 = "DirectX11",
    OpenGL = "OpenGL"
}

USEAPI = GraphicsAPI.DirectX11