set(SampleName condition_variable)

file(GLOB SRC_BASE_LIST  "*.cpp")

add_executable(${SampleName} ${SRC_BASE_LIST})
