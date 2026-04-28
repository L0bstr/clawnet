set(SECTION recv_buffer)

# Core
file(GLOB_RECURSE CORE_SOURCE "core/src/*.c")
add_library(${SECTION}_lib STATIC ${CORE_SOURCE})

set_target_properties(${SECTION}_lib PROPERTIES 
    PREFIX ""
    IMPORT_PREFIX ""
    OUTPUT_NAME "${SECTION}_lib"
)

target_include_directories(${SECTION}_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/core/include")

add_custom_target(${SECTION} DEPENDS ${SECTION}_lib)
