# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\apptictactoe_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\apptictactoe_autogen.dir\\ParseCache.txt"
  "apptictactoe_autogen"
  )
endif()
