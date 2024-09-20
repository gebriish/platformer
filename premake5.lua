workspace "Platformer"
    architecture "x64"
    configurations {
        "Debug", "Release"
    }
    flags
	{
		"MultiProcessorCompile"
	}

    startproject "Platformer"

project "Platformer"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    targetdir "%{wks.location}/bin/%{cfg.name}/%{prj.name}"
    objdir    "%{wks.location}/obj/%{cfg.name}/%{prj.name}"

    files {
        "src/**.cpp",
        "src/**.h"
    }

    includedirs {
        "src",
        "vendor/GLFW/include"
    }

    links {
        "GLFW",
        "Gl"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "on"

        
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "on"


group "dependencies"
    include "vendor/glfw.lua"
group ""