#include "mpsc_queue.h"

MPSCQueue::MPSCQueue(SharedMemory* mem) : mem(mem) {}

bool MPSCQueue::Send(uint32_t type, const void* data, uint32_t size) {
    size_t slot_size = sizeof(Slot) + 256;

    uint64_t pos = mem->tail.fetch_add(1, std::memory_order_relaxed);

    Slot* slot = reinterpret_cast<Slot*>(
        mem->buffer + (pos % mem->slot_count) * slot_size
    );

    uint64_t seq = slot->seq.load(std::memory_order_acquire);
    while (seq != pos) {
        seq = slot->seq.load(std::memory_order_acquire);
    }

    slot->header.type = type;
    slot->header.size = size;

    std::memcpy(slot->data, data, size);

    slot->seq.store(pos + 1, std::memory_order_release);

    return true;
}

std::optional<std::pair<uint32_t, std::string>>
MPSCQueue::Recv(uint32_t expected_type) {
    size_t slot_size = sizeof(Slot) + 256;

    uint64_t pos = mem->head.load(std::memory_order_relaxed);

    Slot* slot = reinterpret_cast<Slot*>(
        mem->buffer + (pos % mem->slot_count) * slot_size
    );

    uint64_t seq = slot->seq.load(std::memory_order_acquire);

    if (seq != pos + 1) {
        return std::nullopt;
    }

    MessageHeader hdr = slot->header;

    std::string payload(hdr.size, '\0');
    std::memcpy(payload.data(), slot->data, hdr.size);

    mem->head.store(pos + 1, std::memory_order_release);

    if (hdr.type != expected_type) {
        return std::nullopt;
    }

    return std::make_pair(hdr.type, payload);
}