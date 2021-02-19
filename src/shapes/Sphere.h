#ifndef SPHERE_H_
#define SPHERE_H_

#include "Solid.h"

class Sphere : public Solid
{
public:
        Sphere(const double r_in=1., const Point& center_in=Eigen::Vector3d::Zero(), const vivid::Color& color_in=vivid::Color(QUVIZ_DEFAULT_COLOR)) :
                Solid(Eigen::Vector3d::Zero(), 0., center_in, color_in), r(r_in) {};

        virtual void draw(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const;

protected:
        double r;
};
#endif
