#pragma

#include <type_traits>
#include <cmath>

namespace structure
{

template <typename T, typename = typename std::enable_if_t<std::is_floating_point_v<T>>>
class Point2D
{
public:
    using value_type = T;
private:
    T x_{static_cast<T>(0)};
    T y_{static_cast<T>(0)};
public:
    Point2D(T x = static_cast<T>(0), T y = static_cast<T>(0)) : x_(x), y_(y)
    {

    }
    Point2D(const Point2D&) = default;
    Point2D& operator=(const Point2D&) = default;
    Point2D(Point2D&&) = default;
    Point2D& operator=(Point2D&&) = default;
public:
    const T& GetX() const noexcept
    {
        return x_;
    }
    const T& GetY() const noexcept
    {
        return y_;
    }
    T& GetX() noexcept
    {
        return x_;
    }
    T& GetY() noexcept
    {
        return y_;
    }
    void SetX(T x = static_cast<T>(0)) noexcept
    {
        x_ = x;
    }
    void SetY(T y = static_cast<T>(0)) noexcept
    {
        y_ = y;
    }
public:
    template <typename U, typename = typename std::enable_if_t<std::is_base_of_v<Point2D, std::decay_t<U>>>>
    T DistOfChebyshev(U && point) const noexcept
    {
        return std::max(std::abs(x_ - std::forward<U>(point).GetX()), std::abs(y_ - std::forward<U>(point).GetY()));
    }
    template <typename U, typename = typename std::enable_if_t<std::is_base_of_v<Point2D, std::decay_t<U>>>>
    T DistOfManhattan(U && point) const noexcept
    {
        return std::abs(x_ - std::forward<U>(point).GetX()) + std::abs(y_ - std::forward<U>(point).GetY());
    }
    template <typename U, typename = typename std::enable_if_t<std::is_base_of_v<Point2D, std::decay_t<U>>>>
    T DistOfEuclidean(U && point) const noexcept
    {
        return std::sqrt(std::pow((x_ - std::forward<U>(point).GetX()), 2) + std::pow(y_ - std::forward<U>(point).GetY()));
    }
    void Translate(T dx = static_cast<T>(0), T dy = static_cast<T>(0)) noexcept
    {
        x_ += dx;
        y_ += dy;
    }
    void Rotate(T angle = static_cast<T>(0)) noexcept
    {
        T radian = angle * static_cast<T>(M_PI) / static_cast<T>(180);
        T new_x = x_ * std::cos(radian) - y_ * std::sin(radian);
        T new_y = x_ * std::sin(radian) + y_ * std::cos(radian);
        x_ = new_x;
        y_ = new_y;
    }
    void Scale(T sx = static_cast<T>(1), T sy = static_cast<T>(1)) noexcept
    {
        x_ *= sx;
        y_ *= sy;
    }
    
};
};

