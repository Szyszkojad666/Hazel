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
	IncludeDir["glm"] = "Hazel/Hazel/Vendor/glm"

	include "Hazel/Hazel/Vendor/GLFW"
	include "Hazel/Hazel/Vendor/Glad"
	include "Hazel/Hazel/Vendor/imgui"

project "Hazel"
	location "Hazel"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("Binary/" ..outputdir .."/%{prj.name}")
	objdir ("Intermediate/" ..outputdir .."/%{prj.name}")

	pchheader "Hzpch.h"
	pchsource "Hazel/Hazel/Source/Hzpch.cpp"

	files
	{
		"%{prj.name}/Hazel/Sourc**.h",
		"%{prj.name}/Hazel/Source/**.cpp",
		"%{prj.name}/Hazel/Vendor/glm/glm/**.hpp",
		"%{prj.name}/Hazel/Vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/Hazel/Source",
		"Hazel/Hazel/Vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows" 
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS",
			"HZ_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
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
	cppdialect "C++17"
	staticruntime "on"

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
		"Hazel/Hazel/Source",
		"Hazel/Hazel/Vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Hazel"
	}

	filter "system:windows" 
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