workspace "Client"
	architecture "x86_64"
	configurations
	{
		"Release",
		"Debug"
	}	

project "Client"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	outputDir = "%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}"

	targetdir ("%{wks.location}/target/" .. outputDir .. "/%{prj.name}")
    objdir ("%{wks.location}/intermediate/" .. outputDir .. "/%{prj.name}")

	files
    {
        "inc/**.h",
        "src/**.cpp"
	}
	
	links
	{
		"Ws2_32.lib"
	}

	includedirs
	{
		"inc"
	}

	filter "configurations:Debug"
        symbols "on"
        runtime "Debug"

    filter "configurations:Release"
        optimize "on"
        runtime "Release"