#include <iostream>
#include <atomic>
#include <chrono>
#include <string>
#include <mutex>
#include <thread>

#include "include/loggertimer.h"
#include "include/first.h"
#include "include/second.h"



int main() {
    std::thread t1(fooFirst);
	std::thread t2(fooSecond);
	t1.join();
	t2.join();
	TIMER_PRINT_STATS();
    return 0;
}
