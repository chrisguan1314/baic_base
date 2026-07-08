#pragma once

#include <type_traits>
#include <stdexcept>

namespace structure
{

template <typename T, typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
class Line2D
{
private:
    Point2D<T> start_{static_cast<T>(0.0), static_cast<T>(0.0)};
    Point2D<T> end_{static_cast<T>(0.0), static_cast<T>(0.0)};
public:
    Line2D(T start_x = static_cast<T>(0.0), T start_y = static_cast<T>(0.0), T end_x = static_cast<T>(0.0), T end_y = static_cast<T>(0.0)) : start_(start_x, start_y), end_(end_x, end_y)
    {

    }
    template <typename U, typename = typename std::enable_if_t<std::is_same_v<Point2D<T>, std::decay_t<U>>>>
    Line2D(U && start, U && end) : start_(std::forward<U>(start)), end_(std::forward<U>(end))
    {

    }
    
    Line2D(const Line2D&) = default;
    Line2D& operator=(const Line2D&) = default;
    Line2D(Line2D&&) = default;
    Line2D& operator=(Line2D&&) = default;
public:
    const Point2D<T>& GetStart() const noexcept
    {
        return start_;
    }
    const Point2D<T>& GetEnd() const noexcept
    {
        return end_;
    }
    Point2D<T>& GetStart() noexcept
    {
        return start_;
    }
    Point2D<T>& GetEnd() noexcept
    {
        return end_;
    }  
    Point2D<T>& operator[](std::size_t index) noexcept
    {
        if (index == 0)
        {
            return start_;
        }
        else if (index == 1)
        {
            return end_;
        }
        else
        {
            throw std::out_of_range("Index out of range. Valid indices are 0 and 1.");
        }
    } 
    template <typename U, typename = typename std::enable_if_t<std::is_same_v<Point2D<T>, std::decay_t<U>>>>
    void SetStart(U && point) noexcept
    {
        start_ = std::forward<U>(point);
    }
    void SetStart(T start_x = static_cast<T>(0.0), T start_y = static_cast<T>(0.0)) noexcept
    {
        start_.SetStart(Point2D<T>(start_x, start_y));
    }
    template <typename U, typename = typename std::enable_if_t<std::is_same_v<Point2D<T>, std::decay_t<U>>>>
    void SetEnd(U && point) noexcept
    {
        end_ = std::forward<U>(point);
    }
    void SetEnd(T end_x = static_cast<T>(0.0), T end_y = static_cast<T>(0.0)) noexcept
    {
        end_.SetEnd(Point2D<T>(end_x, end_y));
    }
};

};