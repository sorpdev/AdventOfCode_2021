project "Day1"

	targetname "Day1"
	targetdir (output)
	objdir (build)

	language "C++"
	kind "ConsoleApp"
	

	files {
		"**.cpp",
		"**.h"
	}
	
	postbuildcommands
  	{
    		"{COPY} \"%{prj.location}/input.txt\" \"%{cfg.targetdir}\""
  	}
