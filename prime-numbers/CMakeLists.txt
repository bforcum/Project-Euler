# Enable Hot Reload for MSVC compilers if supported.
cmake_minimum_required(VERSION 3.8)
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("prime-numbers")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    "config.h"
    "sieve-atkin.h"
    "sieve-eratosthenes.h"
    "bit-manipulation.h"
    "prime-numbers.c"
    "sieve-atkin.c"
    "sieve-eratosthenes.c"
)