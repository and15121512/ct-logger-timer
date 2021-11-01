add_library(out
  ${PROJECT_SOURCE_DIR}/include/out.h
  ${PROJECT_SOURCE_DIR}/include/out.cpp
)

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

if (IS_TIMER_ON)
  target_compile_definitions(main
    PUBLIC IS_TIMER_ON
  )
endif()

if (IS_TIMER_ON)
  target_compile_definitions(out
    PUBLIC IS_TIMER_ON
  )
endif()

if (IS_TIMER_ON)
  target_compile_definitions(first
    PUBLIC IS_TIMER_ON
  )
endif()

if (IS_TIMER_ON)
  target_compile_definitions(second
    PUBLIC IS_TIMER_ON
  )
endif()

if (IS_TIMER_ON)
  target_compile_definitions(loggertimer
    PUBLIC IS_TIMER_ON
  )
endif()

target_link_libraries(main
  out
  first
  second
  loggertimer
)
