#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "Surface.h"

class Rectangle : public Surface
{
public:
        Rectangle(const double a_in, const double b_in, const double angle_in = 0.,
                  const Point& center_in=Eigen::Vector3d::Zero(), const Point& normal_in=Eigen::Vector3d::UnitZ(), const vivid::Color& color_in=vivid::Color(QUVIZ_DEFAULT_COLOR)) :
                Surface(angle_in, center_in, normal_in, color_in), a(a_in), b(b_in) {};

        virtual void draw(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const;

protected:
        double a,b;
};
#endif
