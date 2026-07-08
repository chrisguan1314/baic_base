#pragma once

#include <vector>
#include <algorithm>
#include <limits>
#include <cstdint>

class Dijkstra
{
public:
    Dijkstra() = default;
    
    /**
     * @brief Runs the Dijkstra algorithm on the given graph starting from the specified node.
     * 
     * @param graph The adjacency matrix representing the graph.
     * @param start The starting node for the algorithm.
     */
    void run(const std::vector<std::vector<uint32_t>>& graph, uint32_t start)
    {
        const uint32_t length = graph.size();
        distances.assign(length, std::numeric_limits<uint32_t>::max());
        previous.assign(length, -1);
        visited.assign(length, false);

        distances[start] = 0;

        for (uint32_t i = 0; i < length - 1; ++i)
        {
            // Find the unvisited node with the smallest distance
            uint32_t index_1 = -1;    
            for (uint32_t j = 0; j < length; ++j)
            {
                if (!visited[j] && (index_1 == -1 || distances[j] < distances[index_1]))
                {
                    index_1 = j;
                }
            }

            // If the smallest distance is still infinity, remaining nodes are unreachable
            if (index_1 == -1 || distances[index_1] == std::numeric_limits<uint32_t>::max())
            {
                break;
            }

            // Mark the node as visited
            visited[index_1] = true;

            // Update distances to neighboring nodes
            for (uint32_t index_2 = 0; index_2 < length; ++index_2)
            {
                // 
                if (graph[index_1][index_2] != 0 && !visited[index_2])
                {
                    uint32_t alt = distances[index_1] + graph[index_1][index_2];
                    if (alt < distances[index_2])
                    {
                        distances[index_2] = alt;
                        previous[index_2] = index_1;
                    }
                }
            }
        }
    }
    std::vector<uint32_t> getShortestPath(uint32_t destination) const
    {
        std::vector<uint32_t> path;
        for (uint32_t i = destination; i != -1; i = previous[i])
        {
            path.push_back(i);
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

private:
    std::vector<uint32_t> distances;
    std::vector<uint32_t> previous;
    std::vector<bool> visited;
};