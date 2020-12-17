cmake_minimum_required(VERSION 3.19)
project(multihash C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -g -O2 -std=c99 \
	-Wall -Wextra" )

include_directories(include)
include_directories(tests/c)

add_library(multihash
        include/mh/errors.h
        include/mh/generic.h
        include/mh/hashes.h
        include/mh/multihash.h
        src/errors.c
        src/hashes.c
        src/multihash.c)

add_executable(multihash_bin
        src/main.c
)

add_dependencies(multihash_bin multihash)

# from https://bertvandenbroucke.netlify.app/2019/12/12/unit-testing-with-ctest/

enable_testing()

# Add a new unit test
# A new target with the test sources is constructed, and a CTest test with the
# same name is created. The new test is also added to the global list of test
# contained in the check target
macro(add_unit_test)
    set(options PARALLEL)
    set(oneValueArgs NAME)
    set(multiValueArgs SOURCES LIBS)
    cmake_parse_arguments(TEST "${options}" "${oneValueArgs}"
            "${multiValueArgs}" ${ARGN})
    message(STATUS "generating ${TEST_NAME}")
    add_executable(${TEST_NAME} EXCLUDE_FROM_ALL ${TEST_SOURCES})
    set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
            ${PROJECT_BINARY_DIR}/rundir/test)
    target_link_libraries(${TEST_NAME} ${TEST_LIBS})

    if(TEST_PARALLEL AND HAVE_MPI)
        set(TESTCOMMAND ${MPIEXEC})
        set(TESTARGS ${MPIEXEC_NUMPROC_FLAG} 3 ${MPIEXEC_PREFLAGS}
                "./${TEST_NAME}" ${MPIEXEC_POSTFLAGS})
        set(TESTCOMMAND ${TESTCOMMAND} ${TESTARGS})
    else(TEST_PARALLEL AND HAVE_MPI)
        set(TESTCOMMAND ${TEST_NAME})
    endif(TEST_PARALLEL AND HAVE_MPI)
    add_test(NAME ${TEST_NAME}
            WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/rundir/test
            COMMAND ${TESTCOMMAND})

    set(TESTNAMES ${TESTNAMES} ${TEST_NAME})
endmacro(add_unit_test)

foreach(testfile
        tests/c/test_errors_string.c
        tests/c/test_hashes_code.c
        tests/c/test_hashes_length.c
        tests/c/test_multihash_decoding.c
        tests/c/test_multihash_new.c)

    get_filename_component(name_we ${testfile} NAME_WE)
    set(testfile "${CMAKE_CURRENT_SOURCE_DIR}/${testfile}")
    add_unit_test(NAME ${name_we}
            SOURCES ${testfile}
            LIBS multihash)
endforeach()

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
        DEPENDS ${TESTNAMES})