#pragma once

#include "point2d.h"

namespace structure
{
template <typename T, typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
class Point3D : public Point2D<T>
{
public:
    using value_type = T;
private:
    T z_{static_cast<T>(0)};
public:
    Point3D(T x = static_cast<T>(0), T y = static_cast<T>(0), T z = static_cast<T>(0)) : Point2D<T>(x, y), z_(z)
    {

    }
    Point3D(const Point2D<T>& point, T z = static_cast<T>(0)) : Point2D<T>(point), z_(z)
    {

    }
    Point3D(const Point3D&) = default;
    Point3D& operator=(const Point3D&) = default;
    Point3D(Point3D&&) = default;
    Point3D& operator=(Point3D&&) = default;
public:
    const T& GetZ() const noexcept
    {
        return z_;
    }
    T& GetZ() noexcept
    {
        return z_;
    }
    void SetZ(T z = static_cast<T>(0))
    {
        z_ = z;
    }
public:
    template <typename U, typename = typename std::enable_if_t<std::is_base_of_v<Point3D, std::decay_t<U>>>>
    T DistOfChebyshev(U && point) const noexcept
    {
        return std::max(Point2D<T>::DistOfChebyshev(point), std::abs(z_ - point.GetZ()));
    }
    template <typename U, typename = typename std::enable_if_t<std::is_base_of_v<Point3D, std::decay_t<U>>>>
    T DistOfManhattan(U && point) const noexcept
    {
        return Point2D<T>::DistOfManhattan(point) + std::abs(z_ - point.GetZ());
    }
    template <typename U, typename = typename std::enable_if_t<std::is_base_of_v<Point3D, std::decay_t<U>>>>
    T DistOfEuclidean(U && point) const noexcept
    {
        return std::sqrt(std::pow((Point2D<T>::GetX() - point.GetX()), 2) + std::pow(Point2D<T>::GetY() - point.GetY(), 2) + std::pow(z_ - point.GetZ(), 2));
    }
    void Translate(T dx = static_cast<T>(0), T dy = static_cast<T>(0), T dz = static_cast<T>(0)) noexcept
    {
        Point2D<T>::Translate(dx, dy);
        z_ += dz;
    }
    void Rotate(T angle = static_cast<T>(0)) noexcept
    {
        Point2D<T>::Rotate(angle);
    }
    void Scale(T sx = static_cast<T>(1), T sy = static_cast<T>(1), T sz = static_cast<T>(1)) noexcept
    {
        Point2D<T>::Scale(sx, sy);
        z_ *= sz;
    }
};
};
