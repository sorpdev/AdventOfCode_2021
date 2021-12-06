project "Day2"

	targetname "Day2"
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


