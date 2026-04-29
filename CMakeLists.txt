cmake_minimum_required(VERSION 3.20)
project(trawl C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)

# shared is loaded separately - its libs output to lib/shared instead of lib/<section>
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/shared)
add_subdirectory(sections/shared)

file(GLOB SECTION_DIRS "sections/*/CMakeLists.txt" "sections/*/*/CMakeLists.txt")
list(FILTER SECTION_DIRS EXCLUDE REGEX ".*/shared/CMakeLists.txt")
foreach(section_cmake ${SECTION_DIRS})
   get_filename_component(section_dir ${section_cmake} DIRECTORY)
   get_filename_component(section_parent ${section_dir} DIRECTORY)
   file(RELATIVE_PATH rel ${CMAKE_SOURCE_DIR}/sections ${section_parent})

    # Single-config output path
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${rel}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${rel}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${rel}")

    # Multi-config output path
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/${rel}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib/${rel}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib/${rel}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/${rel}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib/${rel}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib/${rel}")

    add_subdirectory(${section_dir})
endforeach()
