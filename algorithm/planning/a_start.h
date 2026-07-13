#pragma once

#include <vector>
#include <algorithm>
#include <cstdint>
#include <limits>
#include <queue>
#include <stdexcept>
#include <cmath>

// A simple A* implementation for a 2D grid stored as a matrix of costs.
// - grid: non-zero (or non-INF) value indicates traversable cell weight.
// - uses 4-neighborhood (up/down/left/right) and Manhattan heuristic by default.
// - getShortestPath reconstructs path after run.

class AStar
{
public:
    using MapPoint = std::pair<uint32_t, uint32_t>; // (row, col)
    using GridMap = std::vector<std::vector<uint32_t>>; // 2D grid of costs
private:
    // Internal data structures to store g_score, f_score, and path reconstruction info
    std::vector<std::vector<uint32_t>> g_score;
    std::vector<std::vector<uint32_t>> f_score;
    std::vector<std::vector<MapPoint>> came_from;
    GridMap grid_map_;
public:
    AStar(const GridMap& grid_map) : grid_map_(grid_map) {}

    std::vector<MapPoint> GetPath(const MapPoint& start, const MapPoint& goal)
    {
        if (grid_map_.empty() || grid_map_.front().empty())
        {
            throw std::invalid_argument("Grid cannot be empty");
        }
        else if (start == goal)
        {
            throw std::invalid_argument("Start and goal cannot be the same");
        }
                

        const uint32_t rows = static_cast<uint32_t>(grid_map_.size());
        const uint32_t cols = static_cast<uint32_t>(grid_map_.front().size());

        const auto [start_row, start_col] = start;
        const auto [goal_row, goal_col] = goal;

        if (start_row >= rows || start_col >= cols || goal_row >= rows || goal_col >= cols)
        {
            throw std::out_of_range("Start or goal is out of grid bounds");
        }   
        else if (grid_map_[start_row][start_col] == std::numeric_limits<uint32_t>::max() || 
                 grid_map_[goal_row][goal_col] == std::numeric_limits<uint32_t>::max())
        {
            throw std::invalid_argument("Start or goal is not traversable");
        }

        const uint32_t INFINITY_MAX = std::numeric_limits<uint32_t>::max();

        g_score.assign(rows, std::vector<uint32_t>(cols, INFINITY_MAX));
        f_score.assign(rows, std::vector<uint32_t>(cols, INFINITY_MAX));
        came_from.assign(rows, std::vector<MapPoint>(cols, {-1, -1}));

        auto manhattan_dist = [&](const MapPoint& a, const MapPoint& b) -> uint32_t {
            return static_cast<uint32_t>(std::abs(static_cast<int>(a.first) - static_cast<int>(b.first)) +
                                         std::abs(static_cast<int>(a.second) - static_cast<int>(b.second)));
        };

        using MapNode = std::pair<uint32_t, MapPoint>; // (f_score, node)
        struct Compare 
        {
            bool operator()(const MapNode& a, const MapNode& b) const { return a.first > b.first; }
        };

        std::priority_queue<MapNode, std::vector<MapNode>, Compare> open_list;

        g_score[start_row][start_col] = 0;
        f_score[start_row][start_col] = manhattan_dist(start, goal);
        open_list.push({(f_score[start_row][start_col]), start});

        const int dr[4] = {-1, 1, 0, 0};
        const int dc[4] = {0, 0, -1, 1};

        while (!open_list.empty())
        {
            auto [cur_f, current] = open_list.top();
            open_list.pop();

            if (current == goal)
            {
                return getShortestPath(goal);
            }
                
            const uint32_t x = current.first;
            const uint32_t y = current.second;

            // Skip if the current f_score is not up-to-date (stale entry)
            if (cur_f != f_score[x][y])
            {
                continue; // stale
            }
                
            for (std::size_t k = 0; k < 4; ++k)
            {
                int nr = static_cast<int>(x) + dr[k];
                int nc = static_cast<int>(y) + dc[k];
                if (nr < 0 || nc < 0 || nr >= static_cast<uint32_t>(rows) || nc >= static_cast<uint32_t>(cols))
                {
                    continue; // out of bounds
                }
                
                // Skip non-traversable cells
                uint32_t w = grid_map_[nr][nc];
                if (w == 0 || w == INFINITY_MAX)
                {
                    continue; // non-traversable
                }
                    
                // Calculate tentative g_score for neighbor
                uint32_t tentative_g = g_score[x][y];
                if (tentative_g == INFINITY_MAX)
                {
                    continue; // unreachable
                }
                    
                tentative_g += w;

                if (tentative_g < g_score[nr][nc])
                {
                    came_from[nr][nc] = current;
                    g_score[nr][nc] = tentative_g;
                    f_score[nr][nc] = tentative_g + manhattan_dist({static_cast<uint32_t>(nr), static_cast<uint32_t>(nc)}, goal);
                    open_list.push({f_score[nr][nc], {static_cast<uint32_t>(nr), static_cast<uint32_t>(nc)}});
                }
            }
        }
        return {}; // no path found
    }

    std::vector<MapPoint> getShortestPath(const MapPoint& destination) const
    {
        if (came_from.empty() || came_from.front().empty())
        {
            return {};
        }
            
        const uint32_t rows = static_cast<uint32_t>(came_from.size());
        const uint32_t cols = static_cast<uint32_t>(came_from.front().size());

        const auto [dest_row, dest_col] = destination;

        if (dest_row >= rows || dest_col >= cols)
        {
            return {};
        }
            
        const uint32_t INFINITY_MAX = std::numeric_limits<uint32_t>::max();
        if (g_score[dest_row][dest_col] == INFINITY_MAX)
        {
            return {}; // unreachable
        }
            

        std::vector<MapPoint> path;
        MapPoint current_point = destination;
        while (current_point.first != static_cast<uint32_t>(-1) && current_point.second != static_cast<uint32_t>(-1))
        {
            path.push_back(current_point);
            MapPoint temp_point = came_from[current_point.first][current_point.second];
            if (temp_point == current_point)
                break;
            current_point = temp_point;
        }
        std::reverse(path.begin(), path.end());
        return path;
    }
};