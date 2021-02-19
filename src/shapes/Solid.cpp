#include <iostream>

#include "Eigen/Geometry"

#include "Solid.h"

void Solid::rotate(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, const Eigen::Index start, const Eigen::Index size) const
{
        Eigen::Matrix3d rot;
        // rot = Eigen::AngleAxisd(angles(0), Eigen::Vector3d::UnitX()) * Eigen::AngleAxisd(angles(1), Eigen::Vector3d::UnitY()) * Eigen::AngleAxisd(angles(2), Eigen::Vector3d::UnitZ());
        if (std::abs(r_angle) < 1.e-10) {return;}
        assert(std::abs(r_axis.norm()-1.) < 1.e-10);

        rot = Eigen::AngleAxisd(r_angle, r_axis);
        for (Eigen::Index r=start; r<start+size; r++) {
                V.row(r) = V.row(r) * rot;
        }
        

}
