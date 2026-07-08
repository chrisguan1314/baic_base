#pragma once

#include <vector>

namespace algorithm
{

void BubbleSort(std::vector<int>& arr)
{
    const std::size_t n = arr.size();
    for (std::size_t i = 0; i < n - 1; ++i)
    {
        for (std::size_t j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

} // namespace algorithm