workspace "s2d"
	configurations { "Debug", "Release" }
	architecture "x86_64"
	startproject "sandbox"
		
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
	filter {"system:windows"}
		defines {
			"S2D_WINDOWS"
		}
		
	filter {}
	
	include "s2d"
	include "sandbox"
	
	
	
	