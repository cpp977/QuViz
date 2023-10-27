#include <iostream>

#include "Eigen/Geometry"

#include "Arrow.h"
#include "Cone.h"
#include "Cylinder.h"

void Arrow::draw(Eigen::Matrix<double, Eigen::Dynamic, 3>& V,
                 Eigen::Matrix<int, Eigen::Dynamic, 3>& F,
                 Eigen::Matrix<double, Eigen::Dynamic, 3>& C) const
{
    auto curr_size_V = V.rows();

    Cylinder cy((1 - ratio) * h, r, Eigen::Vector3d::UnitZ(), 0., Eigen::Vector3d::Zero(), color);
    Cone co(ratio * h, rhat, Eigen::Vector3d::UnitZ(), 0., 0.5 * h * Eigen::Vector3d::UnitZ(), color);

    cy.draw(V, F, C);
    co.draw(V, F, C);

    this->rotate(V, curr_size_V, V.rows() - curr_size_V);
    this->translate(V, curr_size_V, V.rows() - curr_size_V);
}
