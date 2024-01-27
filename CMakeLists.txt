cmake_minimum_required(VERSION 3.14)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0${PATCH_VERSION})

project(HomeTask4 VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OBJCXX_STANDARD_REQUIRED ON)

configure_file(version.h.in version.h)

Include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.0.1
)

FetchContent_MakeAvailable(Catch2)


add_subdirectory(MetaFunctions)
add_subdirectory(PrintIP)
add_executable(HomeTask4 main.cpp)
add_executable(Tests tests.cpp)

target_link_libraries(HomeTask4 PUBLIC
    PrintIP
)

target_link_libraries(Tests PUBLIC
    Catch2::Catch2WithMain
    MetaFunctions
    PrintIP
)

target_link_libraries(PrintIP PUBLIC
    MetaFunctions
)

target_include_directories(PrintIP PUBLIC
    "${PROJECT_SOURCE_DIR}/MetaFunctions"
)

target_include_directories(HomeTask4 PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/PrintIP"
)

target_include_directories(Tests PUBLIC
    "${PROJECT_SOURCE_DIR}/MetaFunctions"
    "${PROJECT_SOURCE_DIR}/PrintIP"
)

install(TARGETS HomeTask4 RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT alservol@gmail.com)

include(CPack)

enable_testing()

add_test(Tests Tests)
