#ifndef TUBE_H_
#define TUBE_H_

#include "Cylinder.h"

class Tube : public Cylinder
{
public:
        Tube(const double w=1., const Point& start=Eigen::Vector3d::Zero(), const Point& end=Eigen::Vector3d::UnitZ(), const vivid::Color& color_in=vivid::Color(QUVIZ_DEFAULT_COLOR)) :
                Cylinder((end-start).norm(), w, Eigen::Vector3d::Zero() /*Set this later.*/, 0. /*Set this later */, start+0.5*(end-start), color_in, false) {
                assert((end-start).norm()>1.e-10);
                Eigen::Vector3d diff = end-start;
                r_axis = diff.cross(Eigen::Vector3d::UnitZ());//.cross(diff);
                if (r_axis.norm() < 1.e-10) {r_axis=Eigen::Vector3d::UnitX();}
                r_axis/=r_axis.norm();
                r_angle = std::acos(diff.dot(Eigen::Vector3d::UnitZ())/diff.norm());
        };
};
#endif
