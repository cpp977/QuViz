#include <iostream>

#include "Eigen/Geometry"

#include "Rectangle.h"

void Rectangle::draw(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const
{
        auto curr_size_V = V.rows();
        V.conservativeResize(curr_size_V+4,3);
        // p2------------p1
        // |             |
        // |             |b
        // |             |
        // p3------------p4
        //        a
        Point p1 = 0.5*a*Eigen::Vector3d::UnitX() + 0.5*b*Eigen::Vector3d::UnitY();
        Point p2 = 0.5*a*Eigen::Vector3d::UnitX() - 0.5*b*Eigen::Vector3d::UnitY();
        Point p3 = -0.5*a*Eigen::Vector3d::UnitX() - 0.5*b*Eigen::Vector3d::UnitY();
        Point p4 = -0.5*a*Eigen::Vector3d::UnitX() + 0.5*b*Eigen::Vector3d::UnitY();
        V.row(curr_size_V+0) = p1;
        V.row(curr_size_V+1) = p2;
        V.row(curr_size_V+2) = p3;
        V.row(curr_size_V+3) = p4;

        auto curr_size_F = F.rows();
        F.conservativeResize(curr_size_F+2,3);
        F.row(curr_size_F+0) << curr_size_V+2, curr_size_V+1, curr_size_V+0;
        F.row(curr_size_F+1) << curr_size_V+0, curr_size_V+3, curr_size_V+2;

        auto curr_size_C = C.rows();
        C.conservativeResize(curr_size_C+2,3);
        C.row(curr_size_C+0) << color.value()[0], color.value()[1], color.value()[2];
        C.row(curr_size_C+1) << color.value()[0], color.value()[1], color.value()[2];

        this->rotate(V, curr_size_V, 4);
        this->translate(V, curr_size_V, 4);
}
