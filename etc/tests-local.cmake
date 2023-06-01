set(dataset "${PROJECT_SOURCE_DIR}/data")

find_package(Python3 REQUIRED)

if(NOT Python3_FOUND)
    message(FATAL_ERROR "Python3 not found")
endif()

execute_process(
    COMMAND mkdir -p "${dataset}"
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

execute_process(
    COMMAND python3 ${PROJECT_SOURCE_DIR}/data-generation/generate.py
    WORKING_DIRECTORY "${dataset}"
)

add_test(NAME "banded-1024" COMMAND SpMM_test "${dataset}/1024x1024banded_0.bin")
add_test(NAME "banded-2048" COMMAND SpMM_test "${dataset}/2048x2048banded_0.bin")
add_test(NAME "diagonal-1024" COMMAND SpMM_test "${dataset}/1024x1024diagonal_0.bin")
add_test(NAME "diagonal-2048" COMMAND SpMM_test "${dataset}/2048x2048diagonal_0.bin")
add_test(NAME "general-1024" COMMAND SpMM_test "${dataset}/1024x1024general_0.bin")
add_test(NAME "general-2048" COMMAND SpMM_test "${dataset}/2048x2048general_0.bin")
add_test(NAME "symmetric-1024" COMMAND SpMM_test "${dataset}/1024x1024symmetric_0.bin")
add_test(NAME "symmetric-2048" COMMAND SpMM_test "${dataset}/2048x2048symmetric_0.bin")
add_test(NAME "triangular-1024" COMMAND SpMM_test "${dataset}/1024x1024triangular_0.bin")
add_test(NAME "triangular-2048" COMMAND SpMM_test "${dataset}/2048x2048triangular_0.bin")