add_rules("mode.debug", "mode.release")
add_defines("PROJECTDIR=R\"($(projectdir))\"")
--add_defines("PROJECTDIR=\"$(projectdir)\"")
add_defines("BE_DEBUG")
set_languages("clatest", "c++latest")

target("stbimage")
    set_kind("static")
	add_headerfiles("third_lib/stb/**.h")
	add_includedirs("third_lib/stb",{public = true})
	
target("corelibe")
    set_kind("static")
	set_pcxxheader("lib/static/corelib/include/Core/BEPch.h")
	add_files("lib/static/corelib/src/**.cpp")
	add_headerfiles("lib/static/corelib/include/**.h")
	add_includedirs("lib/static/corelib/include",{public = true})

target("texturelib")
    set_kind("static")
	add_headerfiles("lib/static/texturelib/include/**.h")
	add_files("lib/static/texturelib/src/**.cpp")
	
	add_links("libpng16d.lib", "zlibd.lib", "freetyped.lib")
    add_linkdirs("third_lib/lpng1639/build/Debug",
	  "third_lib/zlib-1.2.13/build/lib_output/Debug",
	  "third_lib/freetype-2.13.1/build/Debug")
	--add_files("third_lib/zlib-1.2.13/build/lib_output/Debug/zlibd.lib")	
	--add_files("third_lib/freetype-2.13.1/build/Debug/freetyped.lib")
	
	add_includedirs("third_lib\\freetype-2.13.1\\build\\include\\freetype2")
	add_includedirs("lib/static/texturelib/include",{public = true})
	add_deps("corelibe")
	add_deps("stbimage")

target("cudalib")
    set_kind("static")
    add_files("lib/static/cudalib/src/**.cu")
    add_files("lib/static/cudalib/src/**.cpp")
	add_headerfiles("lib/static/cudalib/inc/**.h")
	add_headerfiles("lib/static/cudalib/inc/**.cuh")
    add_includedirs("lib/static/cudalib/inc",{public = true})
	
	add_defines("SDF_DEBUG")

    add_cuflags("-rdc=true")
    add_cugencodes("native")

	set_policy("build.cuda.devlink", true)
	
    add_deps("corelibe")
	add_deps("texturelib")

target("BEEngine")
    set_kind("binary")
    add_files("src/**.cpp")
	add_headerfiles("include/**.h")
	add_includedirs("include")
	
	--add_includedirs("lib/static/cudalib/inc")
	
	add_deps("cudalib")
	add_deps("corelibe")
	add_deps("texturelib")
	