#pragma once

#include <coroutine>
#include <vector>
#include <unordered_set>
#include <iostream>
#include "generator.h"


Generator<int> dfs(
    const std::vector<std::vector<int>>& graph,
    int node,
    std::unordered_set<int>& visited
) {
    visited.insert(node);

    co_yield node;  // точка кооперативного переключения

    for (int neighbor : graph[node]) {
        if (!visited.count(neighbor)) {
            auto sub = dfs(graph, neighbor, visited);
            while (sub.next()) {
                co_yield sub.value();
            }
        }
    }
}