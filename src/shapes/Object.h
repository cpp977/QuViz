#ifndef OBJECT_H_
#define OBJECT_H_

#include <vector>

#include "Eigen/Dense"

#include "vivid/color.h"

#include "util/macros.h"
#include "GlobalTypedefs.h"

class Object
{
public:
        Object(const Point& center_in=Eigen::Vector3d::Zero(), const vivid::Color& color_in=vivid::Color(QUVIZ_DEFAULT_COLOR)) : center(center_in), color(color_in) {}
        
        virtual void draw(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const = 0;

        void translate(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, const Eigen::Index start, const Eigen::Index size) const;

        virtual ~Object() = default;
protected:
        Point center;
        vivid::Color color;
};
#endif
