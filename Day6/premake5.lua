project "Day6"

	targetname "Day6"
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


