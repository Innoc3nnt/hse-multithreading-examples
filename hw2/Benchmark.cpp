#include <benchmark/benchmark.h>
#include <vector>
#include "ApplyFunction.h"

static void BM_SingleThread_Fast(benchmark::State& state) {
    int n = state.range(0);
    std::vector<int> data(n, 1);

    for (auto _ : state) {
        auto copy = data;
        ApplyFunction<int>(copy, [](int& x) { x += 1; }, 1);
        benchmark::DoNotOptimize(copy);
    }
}

static void BM_MultiThread_Slow(benchmark::State& state) {
    int n = state.range(0);
    std::vector<int> data(n, 1);

    for (auto _ : state) {
        auto copy = data;
        ApplyFunction<int>(copy, [](int& x) { x += 1; }, 8);
        benchmark::DoNotOptimize(copy);
    }
}

static void BM_SingleThread_Slow(benchmark::State& state) {
    int n = state.range(0);
    std::vector<int> data(n, 1);

    for (auto _ : state) {
        auto copy = data;
        ApplyFunction<int>(copy, [](int& x) {
            for (int i = 0; i < 10000; ++i) x += 1;
        }, 1);
        benchmark::DoNotOptimize(copy);
    }
}

static void BM_MultiThread_Fast(benchmark::State& state) {
    int n = state.range(0);
    std::vector<int> data(n, 1);

    for (auto _ : state) {
        auto copy = data;
        ApplyFunction<int>(copy, [](int& x) {
            for (int i = 0; i < 10000; ++i) x += 1;
        }, 8);
        benchmark::DoNotOptimize(copy);
    }
}

BENCHMARK(BM_SingleThread_Fast)->Arg(1000);
BENCHMARK(BM_MultiThread_Slow)->Arg(1000);

BENCHMARK(BM_SingleThread_Slow)->Arg(100000);
BENCHMARK(BM_MultiThread_Fast)->Arg(100000);

BENCHMARK_MAIN();