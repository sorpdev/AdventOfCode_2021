workspace "AdventOfCode_2021"

  cppdialect "C++20"

  platforms { "x64"}

  configurations { "Debug", "Release" }

  startproject "Day1"

  filter "configurations:Debug"
	defines { "DEBUG" }

  filter "configurations:Release"
	defines { "NDEBUG" }
  	optimize "On"

output = "%{wks.location}/bin/%{prj.name}-%{cfg.buildcfg}"
build = "%{wks.location}/build/%{prj.name}-%{cfg.buildcfg}"

group "Projects"
  include "Day1"
  include "Day2"
  include "Day3"
  include "Day4"
  include "Day5"
  include "Day6"
  include "Day7"
group ""
