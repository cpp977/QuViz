#ifndef CUBE_H_
#define CUBE_H_

#include "Cuboid.h"

class Cube : public Cuboid
{
public:
        Cube(const double a_in=1., const Point& center_in=Eigen::Vector3d::Zero(), const RGB& color_in=Palette::red, const Point& r_axis_in=Eigen::Vector3d::Zero(), const double r_angle_in=0.)
                : Cuboid(a_in,a_in,a_in,r_axis_in,r_angle_in,center_in,color_in) {}
};
#endif
