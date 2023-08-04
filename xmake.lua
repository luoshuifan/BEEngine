add_rules("mode.debug", "mode.release")

target("cudalib")
    set_kind("static")
    add_files("lib/static/cudalib/src/*.cu")
    add_files("lib/static/cudalib/src/*.cpp")
	
	add_headerfiles("lib/static/cudalib/inc/*.h")
	add_headerfiles("third_lib/stb/*.h")
    add_includedirs("lib/static/cudalib/inc")

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

target("BEEngine")
    set_kind("binary")
    add_files("src/Test/*.cpp")
	
	add_files("src/BEngine/*.cpp")
	add_files("src/Reflect/*.cpp")
	add_files("src/Render/*.cpp")
	
	add_headerfiles("include/Core/*.h")
	add_headerfiles("include/Reflect/*.h")
	add_headerfiles("include/Render/*.h")
	
	set_pcxxheader("include/pch/BEPch.h")
	
    add_headerfiles("lib/static/cudalib/inc/*.h")
	
	add_deps("cudalib")

--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro definition
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

