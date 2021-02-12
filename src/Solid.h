#ifndef SOLID_H_
#define SOLID_H_

#include "Eigen/Dense"

#include "GlobalTypedefs.h"

#include "Object.h"

class Solid : public Object
{
public:
        Solid(const Point& r_axis_in = Eigen::Vector3d::Zero(), const double r_angle_in=0.,
              const Point& center_in=Eigen::Vector3d::Zero(), const RGB& color_in=Palette::red) : Object(center_in,color_in), r_axis(r_axis_in), r_angle(r_angle_in) {};

        void rotate(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, const Eigen::Index start, const Eigen::Index size) const;
protected:
        Point r_axis;
        double r_angle;
};
#endif
