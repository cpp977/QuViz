#ifndef OBJECT_H_
#define OBJECT_H_

#include "Eigen/Dense"

#include "GlobalTypedefs.h"

#include "colors/RGB.h"
#include "colors/Palette.h"

class Object
{
public:
        Object(const Point& center_in=Eigen::Vector3d::Zero(), const RGB& color_in=Palette::red) : center(center_in), color(color_in) {}
        
        virtual void draw(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const = 0;

        void translate(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, const Eigen::Index start, const Eigen::Index size) const;
protected:
        Point center;
        RGB color;
};
#endif
