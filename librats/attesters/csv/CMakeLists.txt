# Project name
project(attester_csv)

if(NOT BUILD_SHARED_LIBS)
    set(OPENSSL_USE_STATIC_LIBS TRUE)
endif()
find_package (OpenSSL REQUIRED)

find_package (CURL REQUIRED)

# Set include directory
set(INCLUDE_DIRS ${INCLUDE_DIRS}
                 ${CMAKE_CURRENT_SOURCE_DIR}/../../include
                 ${CMAKE_CURRENT_SOURCE_DIR}/../../include/librats
                 ${CMAKE_CURRENT_SOURCE_DIR}/../../include/internal
                 )
include_directories(${INCLUDE_DIRS})

# Set dependency library directory
set(LIBRARY_DIRS ${CMAKE_BINARY_DIR}
                 ${RATS_INSTALL_LIB_PATH}
                 )
link_directories(${LIBRARY_DIRS})

# Set source file
set(SOURCES cleanup.c
            collect_evidence.c
            csv_utils.c
            init.c
            main.c
            pre_init.c
            )

# Generate library
add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${RATS_LDFLAGS} ${RATS_LIB} OpenSSL::Crypto CURL::libcurl)
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${VERSION} SOVERSION ${VERSION_MAJOR})

# Install library
install(TARGETS ${PROJECT_NAME}
        DESTINATION ${RATS_INSTALL_LIBA_PATH})
