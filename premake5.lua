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
IncludeDir["Glad"] = "PlutoniumGameEngine/Dependecies/Glad/include"
IncludeDir["ImGui"] = "PlutoniumGameEngine/Dependecies/imgui"
IncludeDir["glm"] = "PlutoniumGameEngine/Dependecies/glm"

include "PlutoniumGameEngine/Dependecies/GLFW"
include "PlutoniumGameEngine/Dependecies/Glad"
include "PlutoniumGameEngine/Dependecies/imgui"


project "PlutoniumGameEngine"
	location "PlutoniumGameEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pphd.h"
	pchsource "PlutoniumGameEngine/src/pphd.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/Dependecies/glm/glm/**.hpp",
		"%{prj.name}/Dependecies/glm/glm/**.inl",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/Dependecies/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"

	}

	links 
	{ 
		"GLFW",
		"Glad",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PGE_PLATFORM_WINDOWS",
			"PGE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")

		}

	filter "configurations:Debug"
		defines "PGE_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "PGE_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "PGE_DIST"
		buildoptions "/MD"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"%{IncludeDir.glm}"

	}

	links
	{
		"PlutoniumGameEngine"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PGE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "PGE_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "PGE_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "PGE_DIST"
		buildoptions "/MD"
		optimize "On"