if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif()

set(SOURCES logging.cpp)

add_library (flexiobjects SHARED ${SOURCES})

set(CMAKE_C_FLAGS  '-DBUILDING_LIBFLEXI')

set_target_properties(flexiobjects PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories (flexiobjects PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(flexiobjects PUBLIC cxx_std_17)


install(TARGETS flexiobjects
        LIBRARY DESTINATION "lib64/" # source directory
)

set(HEADERS include/flexibleObjects.h include/flexibleObjects.hpp include/logging.h )
install(FILES ${HEADERS}
        DESTINATION "include/flexi/"
)