#include "include/second.h"
#include "include/loggertimer.h"

#include <thread>
#include <chrono>

void fooSecond() {
  using namespace std::chrono_literals;
  TIMER_CREATE(123);
  TIMER_START(123);
  std::this_thread::sleep_for(1000ms);
  TIMER_STOP(123);
}
