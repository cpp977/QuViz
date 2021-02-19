#include <iostream>

#include "Eigen/Geometry"

#include "Surface.h"

void Surface::rotate(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, const Eigen::Index start, const Eigen::Index size) const
{
        Eigen::Matrix3d rot;
        if (normal != Eigen::Vector3d::UnitZ()) {
                // Point rand = Eigen::Vector3d::Random();
                // Point rot_axis = rand  - rand.dot(Eigen::Vector3d::UnitZ())*Eigen::Vector3d::UnitZ();
                // Point rot_axis = Eigen::Vector3d::UnitZ().cross(normal);
                Point rot_axis = normal.cross(Eigen::Vector3d::UnitZ());
                // rot_axis = rot_axis - rot_axis.dot(normal)*normal;
                if (normal == -Eigen::Vector3d::UnitZ()) {rot_axis = Eigen::Vector3d::UnitX();}
                else {rot_axis /= rot_axis.norm();}
                
                // if (rot_axis.dot(Eigen::Vector3d::UnitZ().cross(normal)) > 0.) {rot_axis *= -1.;}
                rot = Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitZ()) * Eigen::AngleAxisd(std::acos(Eigen::Vector3d::UnitZ().dot(normal)), rot_axis);
        }
        else {
                rot = Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitZ());
        }
        for (Eigen::Index r=start; r<start+size; r++) {
                V.row(r) = V.row(r) * rot;
        }
        

}
