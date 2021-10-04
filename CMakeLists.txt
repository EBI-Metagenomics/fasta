cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(
  fasta
  VERSION 0.0.4
  LANGUAGES C)

# Generate compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(external/cmake-boilerplate/cbp.cmake)
cbp_set_rpath()

add_library(fasta src/error.c src/fasta.c src/fsm.c src/tok.c)
add_library(FASTA::fasta ALIAS fasta)

cbp_hide_functions(fasta)
cbp_set_warning_flags()
cbp_ci_build_option()
cbp_generate_export_header(fasta EXPORT_FILE)

target_include_directories(
  fasta
  PUBLIC $<INSTALL_INTERFACE:include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
set_target_properties(fasta PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(fasta PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
target_compile_features(fasta PRIVATE c_std_11)
target_compile_definitions(
  fasta PRIVATE $<$<BOOL:${WIN32}>:_CRT_NONSTDC_NO_DEPRECATE>)
target_compile_definitions(fasta PRIVATE $<$<BOOL:${WIN32}>:__extension__>)
target_compile_options(fasta PRIVATE ${WARNING_FLAGS})
target_compile_options(fasta PRIVATE "-fverbose-asm")
target_link_libraries(fasta INTERFACE $<$<BOOL:${UNIX}>:m>)

cbp_install(fasta MERGED)

enable_testing()
add_subdirectory(test)
