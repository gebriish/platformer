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

    targetdir "%{wks.location}/bin/%{cfg.name}-%{prj.name}"
    objdir    "%{wks.location}/obj/%{cfg.name}-%{prj.name}"

    files {
        "src/**.cpp",
        "src/**.h"
    }

    includedirs {
        "src",
        "vendor/GLFW/include",
        "vendor/GLAD/include",
        "vendor/STB/include"
    }

    links {
        "GLFW",
        "GLAD"
    }

    filter "configurations:Debug"
        runtime "debug"
        defines { "DEBUG" }
        symbols "on"

        
    filter "configurations:Release"
        runtime "release"
        defines { "NDEBUG" }
        optimize "speed"


group "dependencies"
    include "vendor/glfw.lua"
    include "vendor/glad.lua"
group ""
