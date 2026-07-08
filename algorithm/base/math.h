#pragma once

#include "..\..\structure\base\point6d.h"
#include "..\..\structure\base\line2d.h"
#include "..\..\structure\base\line3d.h"
#include <cmath>
#include <type_traits>

namespace algorithm 
{
template <typename T>
decltype(auto) DistOfChebyshev(T && p1, T && p2) 
{
    if constexpr (std::is_same_v<std::decay_t<T>, structure::Point2D<typename std::decay_t<T>::value_type>>)
    {
        return std::max(std::abs(std::forward<T>(p1).GetX() - std::forward<T>(p2).GetX()), std::abs(std::forward<T>(p1).GetY() - std::forward<T>(p2).GetY()));
    }
    else if constexpr (std::is_same_v<std::decay_t<T>, structure::Point3D<typename std::decay_t<T>::value_type>>)
    {
        return std::max(std::max(std::abs(std::forward<T>(p1).GetX() - std::forward<T>(p2).GetX()), std::abs(std::forward<T>(p1).GetY() - std::forward<T>(p2).GetY())), std::abs(std::forward<T>(p1).GetZ() - std::forward<T>(p2).GetZ()));
    }
    else if constexpr (std::is_same_v<std::decay_t<T>, structure::Point6D<typename std::decay_t<T>::value_type>>)
    {
        return std::max(std::max(std::abs(std::forward<T>(p1).GetX() - std::forward<T>(p2).GetX()), std::abs(std::forward<T>(p1).GetY() - std::forward<T>(p2).GetY())), std::abs(std::forward<T>(p1).GetZ() - std::forward<T>(p2).GetZ()));
    }
    else
    {
        static_assert(
            std::is_same_v<std::decay_t<T>, 
            structure::Point2D<typename std::decay_t<T>::value_type>> || std::is_same_v<std::decay_t<T>, structure::Point3D<typename std::decay_t<T>::value_type>> || std::is_same_v<std::decay_t<T>, structure::Point6D<typename std::decay_t<T>::value_type>>, 
            "Unsupported point type");
    }
};

template <typename T>
decltype(auto) DistOfManhattan(T && p1, T && p2) 
{
    if constexpr (std::is_same_v<std::decay_t<T>, structure::Point2D<typename std::decay_t<T>::value_type>>)
    {
        return std::abs(std::forward<T>(p1).GetX() - std::forward<T>(p2).GetX()) + std::abs(std::forward<T>(p1).GetY() - std::forward<T>(p2).GetY());
    }
    else if constexpr (std::is_same_v<std::decay_t<T>, structure::Point3D<typename std::decay_t<T>::value_type>>)
    {
        return std::abs(std::forward<T>(p1).GetX() - std::forward<T>(p2).GetX()) + std::abs(std::forward<T>(p1).GetY() - std::forward<T>(p2).GetY()) + std::abs(std::forward<T>(p1).GetZ() - std::forward<T>(p2).GetZ());
    }
    else if constexpr (std::is_same_v<std::decay_t<T>, structure::Point6D<typename std::decay_t<T>::value_type>>)
    {
        return std::abs(std::forward<T>(p1).GetX() - std::forward<T>(p2).GetX()) + std::abs(std::forward<T>(p1).GetY() - std::forward<T>(p2).GetY()) + std::abs(std::forward<T>(p1).GetZ() - std::forward<T>(p2).GetZ());
    }
    else
    {
        static_assert(
            std::is_same_v<std::decay_t<T>, 
            structure::Point2D<typename std::decay_t<T>::value_type>> || std::is_same_v<std::decay_t<T>, structure::Point3D<typename std::decay_t<T>::value_type>> || std::is_same_v<std::decay_t<T>, structure::Point6D<typename std::decay_t<T>::value_type>>, 
            "Unsupported point type");
    }
};

template <typename T>
decltype(auto) DistOfEuclidean(T && p1, T && p2) 
{
    if constexpr (std::is_same_v<std::decay_t<T>, structure::Point2D<typename std::decay_t<T>::value_type>>)
    {
        auto dx = std::forward<T>(p1).GetX() - std::forward<T>(p2).GetX();
        auto dy = std::forward<T>(p1).GetY() - std::forward<T>(p2).GetY();
        return std::sqrt(dx * dx + dy * dy);
    }
    else if constexpr (std::is_same_v<std::decay_t<T>, structure::Point3D<typename std::decay_t<T>::value_type>>)
    {
        auto dx = std::forward<T>(p1).GetX() - std::forward<T>(p2).GetX();
        auto dy = std::forward<T>(p1).GetY() - std::forward<T>(p2).GetY();
        auto dz = std::forward<T>(p1).GetZ() - std::forward<T>(p2).GetZ();
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }
    else if constexpr (std::is_same_v<std::decay_t<T>, structure::Point6D<typename std::decay_t<T>::value_type>>)
    {
        auto dx = std::forward<T>(p1).GetX() - std::forward<T>(p2).GetX();
        auto dy = std::forward<T>(p1).GetY() - std::forward<T>(p2).GetY();
        auto dz = std::forward<T>(p1).GetZ() - std::forward<T>(p2).GetZ();
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }
    else
    {
        static_assert(
            std::is_same_v<std::decay_t<T>, 
            structure::Point2D<typename std::decay_t<T>::value_type>> || std::is_same_v<std::decay_t<T>, structure::Point3D<typename std::decay_t<T>::value_type>> || std::is_same_v<std::decay_t<T>, structure::Point6D<typename std::decay_t<T>::value_type>>, 
            "Unsupported point type");
    }
};

template <typename T1, typename T2>
decltype(auto) DistFromPointToLine(T1 && point, T2 && line) 
{
    if (std::is_same_v<std::decay_t<T1>, structure::Point2D<typename std::decay_t<T1>::value_type>> && std::is_same_v<std::decay_t<T2>, structure::Line2D<typename std::decay_t<T2>::value_type>>) 
    {
        return std::forward<T2>(line).DistFromPoint(std::forward<T1>(point));
    } 
    else if (std::is_same_v<std::decay_t<T1>, structure::Point3D<typename std::decay_t<T1>::value_type>> && std::is_same_v<std::decay_t<T2>, structure::Line3D<typename std::decay_t<T2>::value_type>>) 
    {
        return std::forward<T2>(line).DistFromPoint(std::forward<T1>(point));
    } 
    else 
    {
        static_assert(
            (std::is_same_v<std::decay_t<T1>, structure::Point2D<typename std::decay_t<T1>::value_type>> && std::is_same_v<std::decay_t<T2>, structure::Line2D<typename std::decay_t<T2>::value_type>>) ||
            (std::is_same_v<std::decay_t<T1>, structure::Point3D<typename std::decay_t<T1>::value_type>> && std::is_same_v<std::decay_t<T2>, structure::Line3D<typename std::decay_t<T2>::value_type>>),
            "Unsupported point or line type"
        );
    }
};

};

