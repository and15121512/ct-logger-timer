#include <iostream>
#include <atomic>
#include <chrono>
#include <string>
#include <mutex>
#include <set>

#ifdef IS_TIMER_ON
#define IS_TIMER_ON

struct timerInfo {
    std::string file;
    size_t line;

    std::string func;
    std::atomic<double> time;
};

bool operator<(const timerInfo& ti1, const timerInfo& ti2) {
    int32_t fileCmp = ti1.file.compare(ti2.file);
    int32_t lineCmp = ti2.line - ti1.line;

    if (fileCmp < 0) {
        return true;
    }
    else if (fileCmp > 0) {
        return false;
    }
    else {
        if (lineCmp < 0) {
            return true;
        }
        else {
            return false;
        }
    }
}

bool operator==(const timerInfo& ti1, const timerInfo& ti2) {
    return (ti1.file == ti2.file)
        && (ti1.line == ti2.line);
}

class Timer {
public:
    Timer(timerInfo* log) : 
        log_(log),
        start_(clock_t::now()) { }
    
    void logElapsed() {
        double delta = std::chrono::duration_cast<second_t>(clock_t::now() - start_).count();
        // ...
    }
private:
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1>>;

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
        if (nullptr == aggregator_) {
            aggregator_ = new Aggregator(1000);
        }
        return aggregator_;
    }

    /*
    * If overflowed then returns nullptr
    * Else returns Timer instance with defined place to log
    */
    Timer* createTimer(const char* timer_id) {
        // ...
        return new Timer(nullptr);
    }
private:
    Aggregator(size_t sz) {
        // ...
        // init by nulls
    }

    ~Aggregator() {
        // ...
    }

    static Aggregator* aggregator_;
    std::set<timerInfo> logs_;
    std::mutex mtx;
};

Aggregator* Aggregator::aggregator_ = nullptr;

#define STRINGIFY_BODY(x) #x
#define STRINGIFY_PROXY(x) STRINGIFY_BODY(x)
#define STRLINE STRINGIFY_PROXY(__LINE__)
#define CONCAT_BODY(a, b) a##b
#define CONCAT_PROXY(a, b) CONCAT_BODY(a, b)
#define TIMER_ID CONCAT_PROXY(__FILE__, STRLINE)

#define TIMER_INSTANCE_BODY(x) Aggregator::getInstance()->createTimer(##x##)
#define TIMER_INSTANCE TIMER_INSTANCE_BODY(TIMER_ID);

#else

//#define TIMER_INSTANCE

#endif // #ifndef TIMER_ON

int main() {
    auto t = TIMER_INSTANCE;
    for (size_t i = 0; i < 1e7; ++i) { }
    t->logElapsed();
    return 0;
}
