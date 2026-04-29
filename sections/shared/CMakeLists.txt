set(SHARED_TARGETS "")

file(GLOB SHARED_SOURCE "core/src/*.c")
foreach(source ${SHARED_SOURCE})
   get_filename_component(name ${source} NAME_WE)

   add_library(${name}_lib STATIC ${source})
   set_target_properties(${name}_lib PROPERTIES 
      PREFIX ""
      IMPORT_PREFIX ""
      OUTPUT_NAME "${name}_lib"
   )
   target_include_directories(${name}_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/core/include")
   list(APPEND SHARED_TARGETS ${name}_lib)
endforeach()

add_custom_target(shared DEPENDS ${SHARED_TARGETS})
