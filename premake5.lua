workspace "PlutoniumGameEngine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "PlutoniumGameEngine/Dependecies/GLFW/include"
IncludeDir["Vulkan"] = "PlutoniumGameEngine/Dependecies/Vulkan/include"
IncludeDir["Glad"] = "PlutoniumGameEngine/Dependecies/Glad/include"
IncludeDir["ImGui"] = "PlutoniumGameEngine/Dependecies/imgui"
IncludeDir["glm"] = "PlutoniumGameEngine/Dependecies/glm"
IncludeDir["stb_image"] = "PlutoniumGameEngine/Dependecies/Stb_image"

include "PlutoniumGameEngine/Dependecies/GLFW"
include "PlutoniumGameEngine/Dependecies/Glad"
include "PlutoniumGameEngine/Dependecies/imgui"

-- Lib directories relative to root folder (solution directory)
LibDir = {}
LibDir["Vulkan"] = "PlutoniumGameEngine/Dependecies/Vulkan/Lib"



project "PlutoniumGameEngine"
	location "PlutoniumGameEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"

	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pphd.h"
	pchsource "PlutoniumGameEngine/src/pphd.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/Dependecies/Stb_image/**.h",
		"%{prj.name}/Dependecies/Stb_image/**.cpp",
		"%{prj.name}/Dependecies/glm/glm/**.hpp",
		"%{prj.name}/Dependecies/glm/glm/**.inl",
	}

	defines{

		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/Dependecies/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Vulkan}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"

	}

	libdirs{
		"%{LibDir.Vulkan}",
		
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"imgui",
		"opengl32.lib",
		"vulkan-1.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"PGE_PLATFORM_WINDOWS",
			"PGE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "PGE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PGE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "PGE_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"PlutoniumGameEngine/Dependecies/spdlog/include",
		"PlutoniumGameEngine/src",
		"PlutoniumGameEngine/Dependecies",
		"%{IncludeDir.glm}"

	}

	links
	{
		"PlutoniumGameEngine"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"PGE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "PGE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PGE_RELEASE"
		runtime "Release"
		optimize "on"
	filter "configurations:Dist"
		defines "PGE_DIST"
		runtime "Release"
		optimize "on"