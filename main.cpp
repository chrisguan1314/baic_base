#include "algorithm\base\math.h"

#include <iostream>

int main()
{
    structure::Point3D<double> p1(1.0, 2.0, 3.0);
    structure::Point3D<double> p2(4.0, 6.0, 8.0);

    auto chebyshev_distance = algorithm::DistOfChebyshev(p1, p2);
    auto manhattan_distance = algorithm::DistOfManhattan(p1, p2);
    auto euclidean_distance = algorithm::DistOfEuclidean(p1, p2);

    std::cout << "Chebyshev Distance: " << chebyshev_distance << std::endl;
    std::cout << "Manhattan Distance: " << manhattan_distance << std::endl;
    std::cout << "Euclidean Distance: " << euclidean_distance << std::endl;

    return 0;
}