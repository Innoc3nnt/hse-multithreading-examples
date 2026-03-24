#include "ProcessPool.h"

ProcessPool::ProcessPool(size_t processes) : workers_(processes) {}

ProcessPool::~ProcessPool() {}