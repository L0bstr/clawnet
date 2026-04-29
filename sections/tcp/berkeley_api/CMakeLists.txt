set(SECTION berkeley_api)

# Core
file(GLOB_RECURSE CORE_SOURCE "core/src/*.c")
add_library(${SECTION}_lib STATIC ${CORE_SOURCE})

set_target_properties(${SECTION}_lib PROPERTIES 
    PREFIX ""
    IMPORT_PREFIX ""
    OUTPUT_NAME "${SECTION}_lib"
)

target_link_libraries(${SECTION}_lib PUBLIC "recv_buffer_lib")
target_include_directories(${SECTION}_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/core/include")

# App
## Client
file(GLOB_RECURSE CLIENT_SOURCE "app/client/*.c")
add_executable(${SECTION}_client ${CLIENT_SOURCE})
target_link_libraries(${SECTION}_client PRIVATE ${SECTION}_lib)

## Server
file(GLOB_RECURSE SERVER_SOURCE "app/server/*.c")
add_executable(${SECTION}_server ${SERVER_SOURCE})
target_link_libraries(${SECTION}_server PRIVATE ${SECTION}_lib)

add_custom_target(${SECTION} DEPENDS ${SECTION}_lib ${SECTION}_client ${SECTION}_server)
