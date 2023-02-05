project "sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "c++17"
	
	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")
	
	files {
		"src/**.h",
		"src/**.cpp"
	}

	links {
		"s2d"
	}
	
	includedirs {
		"../s2d/src"
	}

	
	filter "configurations:Debug"
		defines { "DEBUG" }
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines { "NDEBUG" }
		runtime "Release"
		optimize "On"