add_rules("mode.debug", "mode.release")
add_defines("PROJECTDIR=\"$(projectdir)\"")
add_defines("BE_DEBUG")
set_languages("clatest", "c++latest")

target("texturelib")
    set_kind("static")
	add_headerfiles("lib/static/texturelib/include/*.h")
	add_files("lib/static/texturelib/src/*.cpp")

	add_headerfiles("third_lib/stb/*.h")
	
    add_files("third_lib/lpng1639/build/Debug/libpng16d.lib")	
	add_files("third_lib/zlib-1.2.13/build/lib_output/Debug/zlibd.lib")	
	add_files("third_lib/freetype-2.13.1/build/Debug/freetyped.lib")
	add_includedirs("third_lib/freetype-2.13.1/build/include/freetype2")
	
	add_includedirs("lib/static/texturelib/include")

target("cudalib")
    set_kind("static")
    add_files("lib/static/cudalib/src/*.cu")
    add_files("lib/static/cudalib/src/*.cpp")
	
	add_headerfiles("lib/static/cudalib/inc/*.h")
	add_headerfiles("lib/static/cudalib/inc/*.cuh")
	add_headerfiles("third_lib/stb/*.h")
    add_includedirs("lib/static/cudalib/inc")
	
	add_defines("SDF_DEBUG")

    -- generate relocatable device code for device linker of dependents.
    -- if neither __device__ and __global__ functions will be called cross file or be exported,
    -- nor dynamic parallelism will be used,
    -- this instruction could be omitted.
    add_cuflags("-rdc=true")

    -- generate SASS code for SM architecture of current host
    add_cugencodes("native")

    -- generate PTX code for the virtual architecture to guarantee compatibility
    -- add_cugencodes("compute_30")
    
	set_policy("build.cuda.devlink", true)
	
	add_files("third_lib/lpng1639/build/Debug/libpng16d.lib")
	--add_includedirs("third_lib/lpng1639/build/include")
	
	add_files("third_lib/zlib-1.2.13/build/lib_output/Debug/zlibd.lib")
	--add_includedirs("third_lib/lpng1639/build/include")	
	
	add_files("third_lib/freetype-2.13.1/build/Debug/freetyped.lib")
	add_includedirs("third_lib/freetype-2.13.1/build/include/freetype2")
	add_includedirs("lib/static/texturelib/include")
	add_includedirs("lib/static/cudalib/inc")
	
	add_deps("texturelib")

target("BEEngine")
    set_kind("binary")
    add_files("src/Test/*.cpp")
	
	add_files("src/BEngine/*.cpp")
	add_files("src/Reflect/*.cpp")
	add_files("src/Render/*.cpp")
	add_files("src/Geometry/*.cpp")
	add_files("src/Math/*.cpp")
	
	add_headerfiles("include/Core/*.h")
	add_headerfiles("include/Reflect/*.h")
	add_headerfiles("include/Render/*.h")
	add_headerfiles("include/Geometry/*.h")
	add_headerfiles("include/Math/*.h")
	
	set_pcxxheader("include/pch/BEPch.h")
	
	add_includedirs("include")
	add_includedirs("lib/static/cudalib/inc")
	
	add_deps("cudalib")
	