cmake_minimum_required(VERSION 3.20)
project(trawl C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)

# Static core library
set(LIB "trawl_lib")
file(GLOB_RECURSE LIB_SRC CONFIGURE_DEPENDS "core/src/*.c")
file(GLOB_RECURSE VENDOR_SRC CONFIGURE_DEPENDS "vendor/*.c")
file(GLOB_RECURSE VENDOR_INCLUDES CONFIGURE_DEPENDS "vendor/*/include")
add_library(${LIB} STATIC 
   ${LIB_SRC}
   ${VENDOR_SRC}
)
target_include_directories(${LIB} PUBLIC "core/include")
target_include_directories(${LIB} PUBLIC ${VENDOR_INCLUDES})

## Remove name prefixes
set_target_properties(${LIB} PROPERTIES 
    PREFIX ""
    IMPORT_PREFIX ""
    OUTPUT_NAME "${LIB}"
)

# Client
set(CLIENT "trawl")
file(GLOB_RECURSE CLIENT_SRC CONFIGURE_DEPENDS "app/client/*.c")
add_executable(${CLIENT} ${CLIENT_SRC})
target_link_libraries(${CLIENT} PRIVATE ${LIB})

# Server
set(SERVER "trawld")
file(GLOB_RECURSE SERVER_SRC CONFIGURE_DEPENDS "app/server/*.c")
add_executable(${SERVER} ${SERVER_SRC})
target_link_libraries(${SERVER} PRIVATE ${LIB})

# Single-config output directories
foreach(target ${CLIENT} ${SERVER} ${LIB})
   set_target_properties(${target} PROPERTIES 
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin"
      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib"
      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib"
   )
endforeach()
