#ifndef CONE_H_
#define CONE_H_

#include "Solid.h"

class Cone : public Solid
{
public:
    Cone(const double h_in,
         const double r_in,
         const Point& r_axis_in = Eigen::Vector3d::Zero(),
         const double r_angle_in = 0.,
         const Point& center_in = Eigen::Vector3d::Zero(),
         const vivid::Color& color_in = vivid::Color(QUVIZ_DEFAULT_COLOR))
        : Solid(r_axis_in, r_angle_in, center_in, color_in)
        , h(h_in)
        , r(r_in){};

    virtual void
    draw(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int, Eigen::Dynamic, 3>& F, Eigen::Matrix<double, Eigen::Dynamic, 3>& C) const;

protected:
    double h, r;
    bool DRAW_BASES;
};
#endif
