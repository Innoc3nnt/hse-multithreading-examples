#pragma once
#include <vector>
#include <functional>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include "Future.h"

class ProcessPool {
public:
    explicit ProcessPool(size_t processes);
    ~ProcessPool();

    template<typename Func>
    auto Submit(Func f) -> MyFuture<decltype(f())>;

private:
    size_t workers_;
};

template<typename Func>
auto ProcessPool::Submit(Func f) -> MyFuture<decltype(f())> {
    using R = decltype(f());

    MyPromise<R> promise;
    auto future = promise.get_future();

    int pipefd[2];
    pipe(pipefd);

    pid_t pid = fork();

    if (pid == 0) {
        // child
        close(pipefd[0]);
        R result = f();
        write(pipefd[1], &result, sizeof(result));
        close(pipefd[1]);
        _exit(0);
    } else {
        // parent
        close(pipefd[1]);

        R result;
        read(pipefd[0], &result, sizeof(result));
        close(pipefd[0]);

        waitpid(pid, nullptr, 0);

        promise.set_value(result);
    }

    return future;
}