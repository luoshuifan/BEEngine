if("${CMAKE_SYSTEM_NAME};${CMAKE_CXX_COMPILER_ID}" STREQUAL "AIX;GNU")
  string(APPEND CMAKE_CXX_FLAGS_INIT " -pthread")
endif()
