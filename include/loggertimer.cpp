#include "include/loggertimer.h"

#ifdef IS_TIMER_ON

TimerHolder::TimerHolder(const char* file, size_t line, const char* func) {
	log_ = Aggregator::getInstance()->createTimerInfo(file, line, func);
}

Aggregator* Aggregator::aggregator_ = nullptr;

#endif // #ifdef TIMER_ON
