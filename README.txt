Build tested on VS 2019 (14.2) with VS comand prompt:
1) In "build" directory: cmake -A x64 /* provide "-DIS_TIMER_ON=Y" to enable the timer in your code */
2) cmake --build . --config=Release
3) src\Release\main.exe

Logger-Timer usage:
- The Timer is active and affects perfomance of your program only if you provide "-DIS_TIMER_ON=Y" when it is built with cmake; 
- There are two main macro functions: TIMER_RUN(), TIMER_PRINT_STATS();
- Use TIMER_RUN() to create and run new instance of timer; it will be active until the end of the scope (stops and saves statistics on destructor call);
- To print calculated statistics use TIMER_PRINT_STATS();
