add_library(first
  ${PROJECT_SOURCE_DIR}/include/first.h
  ${PROJECT_SOURCE_DIR}/include/first.cpp
)

add_library(second
  ${PROJECT_SOURCE_DIR}/include/second.h
  ${PROJECT_SOURCE_DIR}/include/second.cpp
)

add_library(loggertimer
  ${PROJECT_SOURCE_DIR}/include/loggertimer.h
  ${PROJECT_SOURCE_DIR}/include/loggertimer.cpp
)

add_executable(main
  main.cpp
)
set_property(TARGET main PROPERTY CXX_STANDARD 17)

target_compile_definitions(main
  PUBLIC IS_TIMER_ON
)

target_compile_definitions(first
  PUBLIC IS_TIMER_ON
)

target_compile_definitions(second
  PUBLIC IS_TIMER_ON
)

target_compile_definitions(loggertimer
  PUBLIC IS_TIMER_ON
)

target_link_libraries(main
  first
  second
  loggertimer
)
