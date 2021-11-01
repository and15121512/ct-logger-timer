#include "include/second.h"
#include "include/loggertimer.h"

#include <thread>
#include <chrono>

void fooSecond() {
  using namespace std::chrono_literals;
  TIMER_RUN();
  std::this_thread::sleep_for(0.1s);
}
