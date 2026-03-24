```bash
Innoc3nt@Innoc3nt:~/Desktop/hse-mutithreading/6/build$ ./tests 
Running main() from ./googletest/src/gtest_main.cc
[==========] Running 4 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 2 tests from ThreadPoolTest
[ RUN      ] ThreadPoolTest.BasicTasks
[       OK ] ThreadPoolTest.BasicTasks (1 ms)
[ RUN      ] ThreadPoolTest.MultipleTasks
[       OK ] ThreadPoolTest.MultipleTasks (0 ms)
[----------] 2 tests from ThreadPoolTest (1 ms total)

[----------] 2 tests from ProcessPoolTest
[ RUN      ] ProcessPoolTest.BasicTasks
[       OK ] ProcessPoolTest.BasicTasks (1 ms)
[ RUN      ] ProcessPoolTest.MultipleTasks
[       OK ] ProcessPoolTest.MultipleTasks (4 ms)
[----------] 2 tests from ProcessPoolTest (6 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 2 test suites ran. (7 ms total)
[  PASSED  ] 4 tests.
```