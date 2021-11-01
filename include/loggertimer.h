#ifndef LOGGERTIMER_H
#define LOGGERTIMER_H

#include <iostream>
#include <iomanip>
#include <atomic>
#include <chrono>
#include <string>
#include <mutex>

//#undef IS_TIMER_ON

#ifdef IS_TIMER_ON

struct timerInfo {
    std::string file;
    size_t line;
    std::string func;
	
	std::atomic<size_t> callsCnt;
    std::atomic<uint64_t> sumTime;
};

struct TimerHolder {
    TimerHolder(const char* file, size_t line, const char* func);
	
    timerInfo* log_;
};

class Timer {
public:
	Timer(TimerHolder* th) : log_(th->log_) {
		start_ = clock_t::now();
	}
	
	~Timer() {
		uint64_t delta = std::chrono::duration_cast<nanosec_t>(clock_t::now() - start_).count();
		log_->callsCnt.fetch_add(1);
        log_->sumTime.fetch_add(delta);
	}
private:
	using clock_t = std::chrono::high_resolution_clock;
    using nanosec_t = std::chrono::nanoseconds;

	timerInfo* log_;
	std::chrono::time_point<clock_t> start_;
};

class Aggregator {
public:
    /* 
    * First call is to be performed by one thread only, e.g.:
    *   std::mutex m;
    *   m.lock();
    *   Aggregator::getInstance();
    *   m.unlock();
    * Next calls can be multithreaded
    */
    static Aggregator* getInstance() {
        // TODO: lock is required before allocation.
        if (nullptr == aggregator_) {
            aggregator_ = new Aggregator(100000);
        }
        return aggregator_;
    }

    timerInfo* createTimerInfo(const char* file, size_t line, const char* func) {
        size_t currSz = currSz_.fetch_add(1);
        if (currSz >= sz_) {
            // TODO: add "written msg" flag checking to avoid huge amount of "overflow" messages logged from each thread.
            mtx.lock();
            std::cerr << "Overflow!" << std::endl;
            mtx.unlock();
            return nullptr;
        }
        logs_[currSz].file = file;
        logs_[currSz].line = line;
        logs_[currSz].func = func;
		logs_[currSz].callsCnt = 0;
        logs_[currSz].sumTime = 0.;
        return logs_ + currSz;
    }

    void printStatistics() {
		std::cout << "----- Statistics on function calls -----" << std::endl;
        std::cout << std::setw(75) << "FILENAME"
                  << std::setw(5) << "LINE"
                  << std::setw(75) << "FUNCTION"
				  << std::setw(10) << "CALLS"
                  << std::setw(10) << "TIME" << std::endl;
        for (size_t i = 0; i < currSz_; ++i) {
            std::cout << std::setw(75) << logs_[i].file
                      << std::setw(5) << logs_[i].line
                      << std::setw(75) << logs_[i].func
					  << std::setw(10) << logs_[i].callsCnt
                      << std::setw(10) << logs_[i].sumTime * 1e-9 << std::endl;
        }
		std::cout << "----------------------------------------" << std::endl;
    }

private:
    Aggregator(size_t sz) : sz_(sz), currSz_(0)/*, isFull_(false)*/ {
        logs_ = new timerInfo[sz_];
    }

    ~Aggregator() {
        delete[] logs_;
    }

    static Aggregator* aggregator_;

    size_t sz_;
    std::atomic<size_t> currSz_;
    timerInfo* logs_;
    //std::atomic<bool> wasFullMsg_;
    
    std::mutex mtx;
};

#define TIMER_RUN() static TimerHolder timer_holder___(__FILE__, __LINE__, __func__); \
		Timer timer___(&timer_holder___);                               
#define TIMER_PRINT_STATS() Aggregator::getInstance()->printStatistics();

#define DUMMY() timer___.dummy();

#else

#define TIMER_RUN()
#define TIMER_PRINT_STATS()

#endif // #ifdef TIMER_ON

#endif // #ifndef LOGGERTIMER_H
