#pragma once

#include <vector>
#include <algorithm>
#include <limits>
#include <cstdint>
#include <stdexcept>
#include <queue>
#include <iostream>

class Dijkstra
{
public:
    Dijkstra() = default;
    
    /**
     * @brief Runs the Dijkstra algorithm on the given graph starting from the specified node.
     * 
     * @param graph The adjacency matrix representing the graph.
     * @param start_index The starting node for the algorithm.
     */
    void run(const std::vector<std::vector<uint32_t>>& graph, uint32_t start_index)
    {
        using distance_pair = std::pair<uint32_t, uint32_t>; // (distance, node_index)

        if (graph.empty() || graph.size() != graph.front().size() || start_index >= graph.size())
        {
            throw std::invalid_argument("Invalid graph or start_index node.");
        }

        const std::size_t length = graph.size();
        // Initialize distances and previous node vectors
        distances.assign(length, std::numeric_limits<uint32_t>::max());
        previous.assign(length, -1);

        // Set the distance to the starting node to 0 and push it onto the priority queue
        distances[start_index] = 0;
        std::priority_queue<distance_pair> queue;
        queue.push({0, start_index});

        while (!queue.empty())
        {
            // structured binding to unpack the top element of the priority queue
            auto [current_distance, current_index] = queue.top();
            queue.pop();

            if (current_distance != distances[current_index])
            {
                continue;
            }

            const auto& neighbors = graph[current_index];
            for (uint32_t neighbor_index = 0; neighbor_index < length; ++neighbor_index)
            {
                uint32_t edge_weight = neighbors[neighbor_index];
                // Skip if the edge weight is 0 (same node) or represents no connection (infinity)
                if (edge_weight == 0 || edge_weight == std::numeric_limits<uint32_t>::max())
                {
                    continue;
                }

                uint32_t new_distance = current_distance + edge_weight;
                // Update the distance and previous node if a shorter path is found
                if (new_distance < distances[neighbor_index])
                {
                    distances[neighbor_index] = new_distance;
                    previous[neighbor_index] = current_index;
                    queue.push({new_distance, neighbor_index});
                }
            }
        }
    }
    std::vector<uint32_t> getShortestPath(uint32_t destination) const
    {
        std::vector<uint32_t> path;
        for (int32_t i = destination; i != -1; i = previous[i])
        {
            std::cout << "i: " << i << std::endl;
            path.push_back(i);
        }
        std::reverse(path.begin(), path.end());
        // rvo  
        return path;
    }
private:
    std::vector<uint32_t> distances;
    std::vector<uint32_t> previous;
};