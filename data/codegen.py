import sys
import os

if len(sys.argv) > 4:
    print('[fatal] Wrong num of args: expected no more than two.')
    exit(1)

funcs_cnt = int(sys.argv[1])
cycles_per_func = sys.argv[2]
calls_cnt = sys.argv[3]

out_h = open('./out.h', 'w+')
out_h.write('#ifndef OUT_H\n')
out_h.write('#define OUT_H\n')
out_h.write('\n')
out_h.write('void trampoline();\n')
out_h.write('\n')
out_h.write('#endif // #ifndef OUT_H\n')

out_cpp = open('./out.cpp', 'w+')
out_cpp.write('#include "include/out.h"\n')
out_cpp.write('#include "include/loggertimer.h"\n')
out_cpp.write('\n')
out_cpp.write('#include <thread>\n')
out_cpp.write('#include <chrono>\n')
out_cpp.write('\n')
for i in range(funcs_cnt):
    out_cpp.write('void foo' + str(i) + '() {\n')
    out_cpp.write('  using namespace std::chrono_literals;\n')
    out_cpp.write('  TIMER_RUN();\n')
    #out_cpp.write('  std::this_thread::sleep_for(0.1s);')
    out_cpp.write('  for (size_t j = 0; j < ' + cycles_per_func + '; ++j) { int x = rand(); }\n')
    out_cpp.write('}\n')
    out_cpp.write('\n')

out_cpp.write('void trampoline() {\n')
out_cpp.write('  for (size_t i = 0; i < ' + calls_cnt +'; ++i) {\n')
for i in range(funcs_cnt):
    out_cpp.write('    foo' + str(i) + '();\n')
out_cpp.write('  }\n')
out_cpp.write('}\n')
out_cpp.write('')
