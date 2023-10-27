#ifndef ARROW_H_
#define ARROW_H_

#include "Solid.h"

class Arrow : public Solid
{
public:
    Arrow(const double h_in,
          const double r_in,
          const double rhat_in,
          const double ratio_in,
          const Point& r_axis_in = Eigen::Vector3d::Zero(),
          const double r_angle_in = 0.,
          const Point& center_in = Eigen::Vector3d::Zero(),
          const vivid::Color& color_in = vivid::Color(QUVIZ_DEFAULT_COLOR),
          const bool DRAW_BASES_IN = true)
        : Solid(r_axis_in, r_angle_in, center_in, color_in)
        , h(h_in)
        , r(r_in)
        , rhat(rhat_in)
        , ratio(ratio_in){};

    virtual void
    draw(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int, Eigen::Dynamic, 3>& F, Eigen::Matrix<double, Eigen::Dynamic, 3>& C) const;

protected:
    double h, r, rhat, ratio;
};
#endif
