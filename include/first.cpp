#include "include/first.h"
#include "include/loggertimer.h"

#include <thread>
#include <chrono>

void fooFirst() {
  using namespace std::chrono_literals;
  TIMER_RUN();
  std::this_thread::sleep_for(1000ms);
}
