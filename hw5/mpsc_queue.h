#pragma once

#include <atomic>
#include <cstdint>
#include <cstring>
#include <optional>
#include <string>

static constexpr uint32_t PROTOCOL_VERSION = 1;

struct MessageHeader {
    uint32_t type;
    uint32_t size;
};

struct Slot {
    std::atomic<uint64_t> seq;
    MessageHeader header;
    char data[];
};

struct SharedMemory {
    uint32_t version;
    uint32_t capacity;
    uint64_t slot_count;

    std::atomic<uint64_t> head;
    std::atomic<uint64_t> tail;

    char buffer[];
};

SharedMemory* CreateShared(const char* name, size_t size, uint64_t slots);
SharedMemory* OpenShared(const char* name, size_t size);

class MPSCQueue {
public:
    explicit MPSCQueue(SharedMemory* mem);

    bool Send(uint32_t type, const void* data, uint32_t size);

    std::optional<std::pair<uint32_t, std::string>> Recv(uint32_t expected_type);

private:
    SharedMemory* mem;
};