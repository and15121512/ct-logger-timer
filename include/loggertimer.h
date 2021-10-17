#ifndef LOGGERTIMER_H
#define LOGGERTIMER_H

#include <iostream>
#include <iomanip>
#include <atomic>
#include <chrono>
#include <string>
#include <mutex>

#ifdef IS_TIMER_ON

struct timerInfo {
    std::string file;
    size_t line;
    std::string func;

    std::atomic<uint64_t> sumTime;
};

class Timer {
public:
    Timer(timerInfo* log) :
        log_(log) { }
    
    void logTime(double delta) {
        log_->sumTime.fetch_add(delta);
    }
private:
    timerInfo* log_;
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
            aggregator_ = new Aggregator(1000);
        }
        return aggregator_;
    }

    Timer* createTimer(const char* file, size_t line, const char* func) {
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
        logs_[currSz].sumTime = 0.;
        return new Timer(logs_ + currSz);
    }

    void printStatistics() {
		std::cout << "----- Statistics on function calls -----" << std::endl;
        std::cout << std::setw(75) << "FILENAME"
                  << std::setw(5) << "LINE"
                  << std::setw(75) << "FUNCTION"
                  << std::setw(10) << "TIME" << std::endl;
        for (size_t i = 0; i < currSz_; ++i) {
            std::cout << std::setw(75) << logs_[i].file
                      << std::setw(5) << logs_[i].line
                      << std::setw(75) << logs_[i].func
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

#define TIMER_CREATE(ID) static auto timer_##ID## = Aggregator::getInstance()->createTimer(__FILE__, __LINE__, __func__); \
        std::chrono::time_point<CLOCK_T> start_time_for_##ID## = CLOCK_T::now();
#define CLOCK_T std::chrono::high_resolution_clock
#define NANOSEC_T std::chrono::nanoseconds
#define TIMER_START(ID) start_time_for_##ID## = CLOCK_T::now();
#define TIMER_STOP(ID) timer_##ID##->logTime(std::chrono::duration_cast<NANOSEC_T>(CLOCK_T::now() - start_time_for_##ID##).count());                                   
#define TIMER_PRINT_STATS() Aggregator::getInstance()->printStatistics();

#else

#define TIMER_CREATE(ID)
#define TIMER_START(ID)
#define TIMER_STOP(ID)
#define TIMER_PRINT_STATS()

#endif // #ifdef TIMER_ON

#endif // #ifndef LOGGERTIMER_H
