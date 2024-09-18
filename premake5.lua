workspace "SimpleGame"
    configurations {
        "Debug", "Release"
    }

project "Platformer"
    kind "ConsoleApp"
    language "C"

    targetdir "%{wks.location}/bin/%{cfg.name}/%{prj.name}"
    objdir    "%{wks.location}/obj/%{cfg.name}/%{prj.name}"

    files {
        "src/**.c",
        "src/**.h"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "on"

        
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "on"