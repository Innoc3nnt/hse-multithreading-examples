#include "mpsc_queue.h"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    const char* name = "/mpsc_demo";
    const size_t size = 1 << 20;

#ifdef PRODUCER
    auto* mem = CreateShared(name, size, 1024);
    MPSCQueue q(mem);

    for (int i = 0; i < 10; ++i) {
        std::string msg = "msg " + std::to_string(i);
        q.Send(1, msg.data(), msg.size());
        std::cout << "Sent: " << msg << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
#endif

#ifdef CONSUMER
    auto* mem = OpenShared(name, size);
    MPSCQueue q(mem);

    while (true) {
        auto res = q.Recv(1);
        if (res) {
            std::cout << "Received: " << res->second << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
#endif

    return 0;
}