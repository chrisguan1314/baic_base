#include "algorithm\base\math.h"
#include "structure\base\line2d.h"


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

    structure::Line2D<double> line1(0.0, 0.0, 3.0, 4.0);
    std::cout << "Line Start: (" << line1[0].GetX() << ", " << line1[0].GetY() << ")" << std::endl;
    std::cout << "Line End: (" << line1[1].GetX() << ", " << line1[1].GetY() << ")" << std::endl;
    std::cout << "Line Length: " << line1.GetLength() << std::endl;
    std::cout << "Line Slope: " << line1.GetSlope() << std::endl;
    structure::Line2D<double> line2(0.0, 4.0, 3.0, 0.0);
    std::cout << "Line2 Start: (" << line2[0].GetX() << ", " << line2[0].GetY() << ")" << std::endl;
    std::cout << "Line2 End: (" << line2[1].GetX() << ", " << line2[1].GetY() << ")" << std::endl;
    std::cout << "Line2 Length: " << line2.GetLength() << std::endl;
    std::cout << "Line2 Slope: " << line2.GetSlope() << std::endl;

    std::cout << "Is cross : " << line1.IsCross(line2) << std::endl;

    structure::Line2D<double> line3 = line1;
    line3.Translate(1.0, 1.0);
    std::cout << "Is cross : " << line1.IsCross(line3) << std::endl;

    return 0;
}