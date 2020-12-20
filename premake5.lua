workspace "Hazel"
	architecture "x64"
	startproject "Sandbox"

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
	IncludeDir["ImGui"] = "Hazel/Hazel/Vendor/imgui"

	include "Hazel/Hazel/Vendor/GLFW"
	include "Hazel/Hazel/Vendor/Glad"
	include "Hazel/Hazel/Vendor/imgui"

project "Hazel"
	location "Hazel"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

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
		"%IncludeDir.Glad",
		"%IncludeDir.ImGui"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
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
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "On"

	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"
		staticruntime "off"

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
		systemversion "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "On"

	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"