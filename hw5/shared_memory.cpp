#include "mpsc_queue.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

SharedMemory* CreateShared(const char* name, size_t size, uint64_t slots) {
    int fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, size);

    void* ptr = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    auto* mem = reinterpret_cast<SharedMemory*>(ptr);

    mem->version = PROTOCOL_VERSION;
    mem->capacity = size;
    mem->slot_count = slots;
    mem->head.store(0);
    mem->tail.store(0);

    size_t slot_size = sizeof(Slot) + 256;
    for (uint64_t i = 0; i < slots; ++i) {
        Slot* slot = reinterpret_cast<Slot*>(mem->buffer + i * slot_size);
        slot->seq.store(i);
    }

    return mem;
}

SharedMemory* OpenShared(const char* name, size_t size) {
    int fd = shm_open(name, O_RDWR, 0666);
    void* ptr = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    auto* mem = reinterpret_cast<SharedMemory*>(ptr);

    if (mem->version != PROTOCOL_VERSION) {
        std::cerr << "Protocol mismatch!" << std::endl;
        std::exit(1);
    }

    return mem;
}