add_executable(main
  main.cpp
)
set_property(TARGET main PROPERTY CXX_STANDARD 17)

target_compile_definitions(main
  PUBLIC IS_TIMER_ON
)

#target_link_libraries(main

#)
