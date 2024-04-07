# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "examples\\Aliyun\\Aliyun_autogen"
  "examples\\Aliyun\\CMakeFiles\\Aliyun_autogen.dir\\AutogenUsed.txt"
  "examples\\Aliyun\\CMakeFiles\\Aliyun_autogen.dir\\ParseCache.txt"
  "examples\\template\\CMakeFiles\\template_autogen.dir\\AutogenUsed.txt"
  "examples\\template\\CMakeFiles\\template_autogen.dir\\ParseCache.txt"
  "examples\\template\\template_autogen"
  )
endif()
