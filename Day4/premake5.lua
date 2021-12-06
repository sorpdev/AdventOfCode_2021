project "Day4"

	targetname "Day4"
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


