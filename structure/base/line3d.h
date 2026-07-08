#pragma once

#include "point3d.h"
#include <type_traits>

namespace structure
{

template <typename T, typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
class Line3D 
{
public:
    using value_type = T;
private:
    Point3D<T> start_{static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)};
    Point3D<T> end_{static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)};
public: 
    Line3D(T start_x = static_cast<T>(0), T start_y = static_cast<T>(0), T start_z = static_cast<T>(0), T end_x = static_cast<T>(0), T end_y = static_cast<T>(0), T end_z = static_cast<T>(0)) : start_(start_x, start_y, start_z), end_(end_x, end_y, end_z)
    {

    }
    template <typename U, typename = typename std::enable_if_t<std::is_same_v<Point3D<T>, std::decay_t<U>>>>
    Line3D(U && start, U && end) : start_(std::forward<U>(start)), end_(std::forward<U>(end))
    {

    }
    
    Line3D(const Line3D&) = default;
    Line3D& operator=(const Line3D&) = default;
    Line3D(Line3D&&) = default;
    Line3D& operator=(Line3D&&) = default;
public:
    const Point3D<T>& GetStart() const noexcept
    {
        return start_;
    }
    const Point3D<T>& GetEnd() const noexcept
    {
        return end_;
    }
    Point3D<T>& GetStart() noexcept
    {
        return start_;
    }
    Point3D<T>& GetEnd() noexcept
    {
        return end_;
    }
    void SetStart(T start_x = static_cast<T>(0), T start_y = static_cast<T>(0), T start_z = static_cast<T>(0)) noexcept
    {
        start_.SetX(start_x);
        start_.SetY(start_y);
        start_.SetZ(start_z);
    }
    template <typename U, typename = typename std::enable_if_t<std::is_same_v<Point3D<T>, std::decay_t<U>>>>
    void SetStart(U && point) noexcept
    {
        start_ = std::forward<U>(point);
    }
    void SetEnd(T end_x = static_cast<T>(0), T end_y = static_cast<T>(0), T end_z = static_cast<T>(0)) noexcept
    {
        end_.SetX(end_x);
        end_.SetY(end_y);
        end_.SetZ(end_z);
    }
    template <typename U, typename = typename std::enable_if_t<std::is_same_v<Point3D<T>, std::decay_t<U>>>>
    void SetEnd(U && point) noexcept    
    {
        end_ = std::forward<U>(point);
    }
    Point3D<T>& operator[](std::size_t index) noexcept
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
            throw std::out_of_range("Index out of bounds");
        }
    }
public:
    T GetLength() const noexcept
    {
        return start_.DistOfEuclidean(end_);
    }
    T DistFromPoint(const Point3D<T>& point) const noexcept
    {
        // Implementation for distance from a point to the line
    }
    bool IsPointOnLine(const Point3D<T>& point, T tolerance = std::numeric_limits<T>::epsilon()) const noexcept
    {
        // Implementation for checking if a point is on the line
    }
    template <typename U, typename = typename std::enable_if_t<std::is_same_v<Line3D<T>, std::decay_t<U>>>>
    bool IsCross(U && other) const noexcept
    {
        // Implementation for checking if two lines cross
    }
    void Translate(T dx = static_cast<T>(0.0), T dy = static_cast<T>(0.0), T dz = static_cast<T>(0.0)) noexcept
    {
        start_.Translate(dx, dy, dz);
        end_.Translate(dx, dy, dz);
    }
};

};


