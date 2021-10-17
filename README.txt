Build tested on VS 2019 (14.2) with VS comand prompt:
1) In "build" directory: cmake -A x64
2) cmake --build . --config=Release
3) src\Release\main.exe

Logger-Timer usage:
- There are four main macro functions: TIMER_CREATE(_timer_id_), TIMER_START(_timer_id_), TIMER_STOP(_timer_id_), TIMER_PRINT_STATS();
- On TIMER_CREATE(_timer_id_) new instance of timer called _timer_id_ is created; it can be thought as simple static variable inside function;
- By default timer is already run by TIMER_CREATE(_timer_id_); to put calculated time in Aggregator one should use TIMER_STOP(_timer_id_);
- The timer could be used again by calling TIMER_START(_timer_id_);
- To print calculated statistics use TIMER_PRINT_STATS();
