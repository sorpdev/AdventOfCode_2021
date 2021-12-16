project "Day7"

	targetname "Day7"
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


