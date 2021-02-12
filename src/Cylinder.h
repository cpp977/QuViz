#ifndef CYLINDER_H_
#define CYLINDER_H_

#include "Solid.h"

class Cylinder : public Solid
{
public:
        Cylinder(const double h_in, const double r_in, const Point& r_axis_in = Eigen::Vector3d::Zero(), const double r_angle_in=0.,
                 const Point& center_in=Eigen::Vector3d::Zero(), const RGB& color_in=Palette::red, const bool DRAW_BASES_IN=true) :
                Solid(r_axis_in, r_angle_in, center_in, color_in), h(h_in), r(r_in), DRAW_BASES(DRAW_BASES_IN) {};

        virtual void draw(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const;

protected:
        double h,r;
        bool DRAW_BASES;
};
#endif
