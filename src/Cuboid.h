#ifndef CUBOID_H_
#define CUBOID_H_

#include "colors/Palette.h"
#include "Solid.h"

class Cuboid : public Solid
{
public:
        Cuboid(const double a_in, const double b_in, const double c_in,
               const Point& r_axis_in = Eigen::Vector3d::Zero(), const double r_angle_in=0., const Point& center_in=Eigen::Vector3d::Zero(), const RGB& color_in=Palette::red) :
                Solid(r_axis_in, r_angle_in, center_in, color_in), a(a_in), b(b_in), c(c_in) {};

        virtual void draw(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const;
        
protected:
        double a,b,c;
};
#endif
