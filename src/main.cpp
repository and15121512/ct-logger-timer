#include <iostream>
#include <vector>
#include <atomic>
#include <chrono>
#include <string>
#include <mutex>
#include <thread>

#include "include/loggertimer.h"
#include "include/first.h"
#include "include/second.h"
#include "include/out.h"

class MyTimer {
 private:
  using clock_t = std::chrono::high_resolution_clock;
  using second_t = std::chrono::duration<double, std::ratio<1>>;

  std::chrono::time_point<clock_t> m_beg;

 public:
  MyTimer() : m_beg(clock_t::now()) { }

  void reset() { m_beg = clock_t::now(); }

  double elapsed() const {
    return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
  }
};

//void trampoline() {
//	for (size_t i = 0; i < 10; ++i) {
//		fooSecond();
//	}
//}

int main() {
	
	MyTimer tim;
	
	std::thread t1(trampoline);
	std::thread t2(trampoline);
	std::thread t3(trampoline);
	std::thread t4(trampoline);
	std::thread t5(trampoline);
	std::thread t6(trampoline);
	std::thread t7(trampoline);
	std::thread t8(trampoline);
	std::thread t9(trampoline);
	std::thread t10(trampoline);
	
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();
	t9.join();
	t10.join();
	
	double delta = tim.elapsed();
	
	TIMER_PRINT_STATS();
	
	std::cout << "TOTAL WORKING TIME:" << delta << std::endl;
	
    return 0;
}
