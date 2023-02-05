project "s2d"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	characterset "ASCII"
	
	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")
	
	files {
		"src/**.h",
		"src/**.cpp"
	}
	

	
	filter "configurations:Debug"
		defines { "DEBUG" }
		runtime "Debug"
		optimize "Off"
		symbols "On"
		
	filter "configurations:Release"
		defines { "NDEBUG" }
		runtime "Release"
		optimize "On"
	