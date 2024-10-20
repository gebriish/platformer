workspace "Engine"
    architecture "x86_64"
    configurations {
        "Debug", "Release"
    }
    flags
    {
        "MultiProcessorCompile"
    }
    startproject "Platformer"

include "Platformer/platformer.lua"
