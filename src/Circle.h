#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "Polygon.h"

class Circle : public Polygon
{
public:
        Circle(const double r_in, const Point& center_in=Eigen::Vector3d::Zero(), const Point& normal_in=Eigen::Vector3d::UnitZ(), const RGB& color_in=Palette::red) :
                Polygon(50, r_in, 0., center_in, normal_in, color_in) {};
};
#endif
