-- require("cmake")

workspace("sqlite3_orm")
    configurations({"Debug","Release"})
	platforms {"Win32","Win64","Linux"}
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
			"thirdparty/sqlite/**.h*",
			"thirdparty/sqlite/**.c*",
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
			"thirdparty/sqlite"
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

-- Tests
	project "tests"
	   kind "ConsoleApp"
	   language "C++"
	   cppdialect "C++14"
	   targetdir "bin/%{cfg.buildcfg}"
	   targetname "ut_tests"
	   objdir "obj"
	   
	    files({
			"include/**.h*",
			"src/**.h*",
			"src/**.c*",
			"thirdparty/sqlite/**.h*",
			"thirdparty/sqlite/**.c*",
			"tests/tests.c*",
		})

	   dependson ({
		   "Gtestlib"
	   })
	   
	   includedirs({
			"include",
			"thirdparty/sqlite",
			"thirdparty/gtest/googletest/include",
			  --"thirdparty/gtest/googlemock/include"
		})

		libdirs{
			"thirdparty/gtest/build/lib/%{cfg.buildcfg}"
		}

		links{
			"gtest",
			"gtest_main",
			"gmock",
			"gmock_main"
		}
		
		defines ({
			-- "SD_ENABLE_IRRKLANG"
		})

		warnings "Off"

	  filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	  filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"

	  filter  "platforms:Win32"
		defines{"WIN32"}
		system "windows"
		architecture "x32"
		staticruntime "on"
		
	  filter  "platforms:Win64"
		defines{"WIN64"}
		system "windows"
		architecture "x64"
		staticruntime "on"
		
	  filter  "platforms:Linux"
		defines{"LINUX"}
		system "linux"


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
			"include"
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
			
	
	project "Gtestlib"
		kind "Makefile"
		location("thirdparty/gtest")
		includedirs{"./include"}
		
		cleancommands {
			"{RMDIR} %{prj.location}/build/"
		}
		
		filter "configurations:Debug"
			targetdir "%{prj.location}/build"
		
		buildcommands {
			"cmake -DGTEST_LINKED_AS_SHARED=0 %{prj.location} -B %{cfg.targetdir}",
			"cmake --build %{cfg.targetdir}"
		}
		
		rebuildcommands {
			"{RMDIR} %{prj.location}/build/",
			"cmake -DGTEST_LINKED_AS_SHARED=0 %{prj.location} -B %{cfg.targetdir}",
			"cmake --build %{cfg.targetdir}"
		}
		
		filter "configurations:Release"
			targetdir "t%{prj.location}/build"
		
		buildcommands {
			"cmake -DCMAKE_BUILD_TYPE=Release %{prj.location} -B %{cfg.targetdir}",
			"cmake --build %{cfg.targetdir} --config Release"
		}
		
		rebuildcommands {
			"{RMDIR} %{prj.location}/build/",
			"cmake -DCMAKE_BUILD_TYPE=Release %{prj.location} -B %{cfg.targetdir}",
			"cmake --build %{cfg.targetdir} --config Release"
		}