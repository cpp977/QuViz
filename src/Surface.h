#ifndef SURFACE_H_
#define SURFACE_H_

#include "Eigen/Dense"

#include "GlobalTypedefs.h"
#include "Object.h"

class Surface : public Object
{
public:
        Surface(const double& angle_in, const Point& center_in=Eigen::Vector3d::Zero(), const Point& normal_in=Eigen::Vector3d::UnitZ(), const RGB& color_in=Palette::red) : Object(center_in, color_in), angle(angle_in), normal(normal_in) {};

        void rotate(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, const Eigen::Index start, const Eigen::Index size) const;
protected:
        double angle;
        Point normal;
};
#endif
