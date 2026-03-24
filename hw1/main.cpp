#include <vector>
#include <unordered_set>
#include "dfs.h"
#include "generator.h"

int main() {
    std::vector<std::vector<int>> graph = {
        {1, 2, 3}, // 0
    
        {4, 5}, // 1
        {6, 7}, // 2
        {8, 9}, // 3
    
        {10, 11}, // 4
        {12, 13}, // 5
        {14, 15}, // 6
        {16, 17}, // 7
        {18, 19}, // 8
        {20, 21}, // 9
    
        {22, 23}, // 10
        {24, 25}, // 11
        {26, 27}, // 12
        {28, 29}, // 13
        {30, 31}, // 14
        {32, 33}, // 15
        {34, 35}, // 16
        {36, 37}, // 17
        {38, 39}, // 18
        {40, 41}, // 19
        {42, 43}, // 20
        {44, 45}, // 21
    
        {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}
    };

    std::unordered_set<int> visited;

    auto gen = dfs(graph, 0, visited);

    while (gen.next()) {
        std::cout << "Visited: " << gen.value() << std::endl;
    }
}