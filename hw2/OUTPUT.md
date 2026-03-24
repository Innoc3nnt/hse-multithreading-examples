# Tests
``` bash
Innoc3nt@Innoc3nt:~/Desktop/hse-mutithreading/2/build$ ./tests
Running main() from ./googletest/src/gtest_main.cc
[==========] Running 5 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 5 tests from ApplyFunctionTest
[ RUN      ] ApplyFunctionTest.SingleThread
[       OK ] ApplyFunctionTest.SingleThread (0 ms)
[ RUN      ] ApplyFunctionTest.MultiThread
[       OK ] ApplyFunctionTest.MultiThread (0 ms)
[ RUN      ] ApplyFunctionTest.MoreThreadsThanElements
[       OK ] ApplyFunctionTest.MoreThreadsThanElements (0 ms)
[ RUN      ] ApplyFunctionTest.EmptyVector
[       OK ] ApplyFunctionTest.EmptyVector (0 ms)
[ RUN      ] ApplyFunctionTest.HeavyFunctionCorrectness
[       OK ] ApplyFunctionTest.HeavyFunctionCorrectness (0 ms)
[----------] 5 tests from ApplyFunctionTest (2 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 1 test suite ran. (2 ms total)
[  PASSED  ] 5 tests.
```

# Benchmark

В бенчмарке есть два сценария: 
1. Однопоточный быстрее
    - Маленький массив (1000)
    - Очень лёгкая операция (x += 1)
    - Накладные расходы на потоки больше, чем польза

2. Многопоточный быстрее
    - Большой массив (100000)
    - Тяжёлая операция (цикл на 10000 итераций)
    - Выигрыш за счёт параллелизма

``` bash
Innoc3nt@Innoc3nt:~/Desktop/hse-mutithreading/2/build$ ./bench 
2026-03-24T20:53:23+00:00
Running ./bench
Run on (6 X 4192.02 MHz CPU s)
Load Average: 1.01, 1.21, 1.23
***WARNING*** Library was built as DEBUG. Timings may be affected.
----------------------------------------------------------------------
Benchmark                            Time             CPU   Iterations
----------------------------------------------------------------------
BM_SingleThread_Fast/1000        24109 ns        24110 ns        28890
BM_MultiThread_Slow/1000       1600903 ns      1344466 ns          420
BM_SingleThread_Slow/100000  720478482 ns    720529107 ns            1
BM_MultiThread_Fast/100000   185939703 ns      3360477 ns          100
```