#include <iostream>

#include "Eigen/Geometry"

#include "Object.h"

void Object::translate(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, const Eigen::Index start, const Eigen::Index size) const
{
        for (Eigen::Index r=start; r<start+size; r++) {
                V.row(r) += center.transpose();
        }
}
