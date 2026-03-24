# Tests
``` bash
Innoc3nt@Innoc3nt:~/Desktop/hse-mutithreading/3/build$ ./buffered_channel_test 
Running main() from ./googletest/src/gtest_main.cc
[==========] Running 6 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 6 tests from Correctness
[ RUN      ] Correctness.Simple
[       OK ] Correctness.Simple (301 ms)
[ RUN      ] Correctness.Senders
[       OK ] Correctness.Senders (302 ms)
[ RUN      ] Correctness.Receivers
[       OK ] Correctness.Receivers (304 ms)
[ RUN      ] Correctness.SmallBuf
[       OK ] Correctness.SmallBuf (304 ms)
[ RUN      ] Correctness.BigBuf
[       OK ] Correctness.BigBuf (337 ms)
[ RUN      ] Correctness.Random
[       OK ] Correctness.Random (311 ms)
[----------] 6 tests from Correctness (1861 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 1 test suite ran. (1861 ms total)
[  PASSED  ] 6 tests.
```

# Benchmark

```bash
Innoc3nt@Innoc3nt:~/Desktop/hse-mutithreading/3/build$ ./buffered_channel_benchmark 
2026-03-24T21:00:07+00:00
Running ./buffered_channel_benchmark
Run on (6 X 4192.02 MHz CPU s)
Load Average: 1.41, 1.52, 1.42
***WARNING*** Library was built as DEBUG. Timings may be affected.
-----------------------------------------------------------------------------------------------
Benchmark                                                     Time             CPU   Iterations
-----------------------------------------------------------------------------------------------
Run/2/2/4/min_time:0.100/process_time/real_time           44040 ms        56389 ms            1
Run/10/3/3/min_time:0.100/process_time/real_time          13795 ms        19382 ms            1
Run/100000/3/3/min_time:0.100/process_time/real_time        153 ms          321 ms            1
```