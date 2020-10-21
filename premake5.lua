workspace "Hazel"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-{cfg.system}-%{cfg.architecture}"

	IncludeDir = {}
	IncludeDir["GLFW"] = "Hazel/Hazel/Vendor/GLFW/include"
	IncludeDir["Glad"] = "Hazel/Hazel/Vendor/Glad/include"

	include "Hazel/Hazel/Vendor/GLFW"
	include "Hazel/Hazel/Vendor/Glad"

project "Hazel"
	location "Hazel"
	kind "SharedLib"
	language "C++"

	targetdir ("Binary/" ..outputdir .."/%{prj.name}")
	objdir ("Intermediate/" ..outputdir .."/%{prj.name}")

	pchheader "Hzpch.h"
	pchsource "Hazel/Hazel/Source/Hzpch.cpp"

	files
	{
		"%{prj.name}/Hazel/Source/**.h",
		"%{prj.name}/Hazel/Source/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/Hazel/Source",
		"Hazel/Hazel/Vendor/spdlog/include",
		"%IncludeDir.GLFW",
		"%IncludeDir.Glad"
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows" 
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS",
			"HZ_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} ../Binary/" .. outputdir .. "/Sandbox")
	}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "HZ_DIST"
		buildoptions "/MD"
		optimize "On"

	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"

	targetdir ("Binary/" ..outputdir .."/%{prj.name}")
	objdir ("Intermediate/" ..outputdir .."/%{prj.name}")

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp"
	}

	includedirs
	{
		"Hazel/Hazel/Vendor/spdlog/include",
		"Hazel/Hazel/Source"
	}

	links
	{
		"Hazel"
	}

	filter "system:windows" 
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "HZ_DIST"
		buildoptions "/MD"
		optimize "On"

	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"