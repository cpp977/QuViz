#ifndef SQUARE_H_
#define SQUARE_H_

#include "Rectangle.h"

class Square : public Rectangle
{
public:
        Square(const double a_in, const double angle_in, const Point& center_in=Eigen::Vector3d::Zero(),
               const Point& normal_in=Eigen::Vector3d::UnitZ(), const vivid::Color& color_in=vivid::Color(QUVIZ_DEFAULT_COLOR)) :
                Rectangle(a_in, a_in, angle_in, center_in, normal_in, color_in) {};
};
#endif