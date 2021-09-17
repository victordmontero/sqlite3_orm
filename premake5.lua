require("cmake")

workspace("sqlite3_orm")
    configurations({"Debug","Release"})
    location("build/%{_ACTION}")

    project("sqlite3_orm")
        kind("StaticLib")
        language("C++")
        targetdir("bin/%{cfg.buildcfg}/lib")
		cppdialect("C++98")

        files({
			"include/**.h*",
			"src/**.h*",
			"src/**.c*",
			"thirdparty/**.h*",
			"thirdparty/**.c*",
			"**.lua"
		})

		defines{
			"SQLITE3_ORM_WIN32"
		}

		undefines{
			"SQLITE3_ORM_EVO"
		}

        includedirs{
			"include",
			"thirdparty"
		}

		libdirs{
			"thirdparty"
		}

        filter("configurations:Debug")
            defines({
				"DEBUG"
			})
            symbols("On")

        filter("configurations:Release")
            defines({"NDEBUG"})
            optimize("On")


	local checklib_dir = "C:/Users/vmontero/Documents/Proyectos/check/out/build"
-- Tests			
	project("tests")
        kind("ConsoleApp")
        language("C++")
        targetdir("bin/%{cfg.buildcfg}/tests")

        files({
			"tests/tests.c*",
		})

		defines{
			"SQLITE3_ORM_WIN32"
		}

        includedirs{
			"include",
			"thirdparty",
			checklib_dir,
			checklib_dir.."/src"
		}
		
        links{
			"sqlite3_orm",
			"check"
		}

        filter("configurations:Debug")
            defines({"DEBUG"})
            symbols("On")
			
			libdirs{
				checklib_dir.."/src/Debug"
			}

        filter("configurations:Release")
            defines({"NDEBUG"})
            optimize("On")
			
			libdirs{
				checklib_dir.."/src/Release"
			}


-- Examples			
	project("demo")
        kind("ConsoleApp")
        language("C++")
        targetdir("bin/%{cfg.buildcfg}/demo")

        files({
			"demo/**.c*",
		})

		defines{
			"SQLITE3_ORM_WIN32"
		}

        includedirs{
			"include",
			"thirdparty"
		}
		
        links{
			"sqlite3_orm",
		}

        filter("configurations:Debug")
            defines({"DEBUG"})
            symbols("On")

        filter("configurations:Release")
            defines({"NDEBUG"})
            optimize("On")