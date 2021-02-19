#ifndef LATTICE_DEFS_H_
#define LATTICE_DEFS_H_

#include "Eigen/Dense"
#include "Eigen/Geometry"

#include "GlobalTypedefs.h"

namespace Lattice {

enum class TRIANG_TYPE {
        XC=0,
        YC=1
};
        
std::tuple<std::array<Point,2>, std::vector<double>, std::vector<Point> > make_square(double lattice_constant, std::size_t furthest_neighbor) {
        assert(furthest_neighbor <= 4);
        std::array<Point,2> basis = {lattice_constant * Eigen::Vector3d::UnitX(), lattice_constant * Eigen::Vector3d::UnitY()};
        std::vector<double> neighbor_distance(furthest_neighbor+1);
        neighbor_distance[0] = 0.;
        if (furthest_neighbor>0) {neighbor_distance[1] = lattice_constant;}
        if (furthest_neighbor>1) {neighbor_distance[2] = std::sqrt(2.)*lattice_constant;}
        if (furthest_neighbor>2) {neighbor_distance[3] = 2.*lattice_constant;}
        if (furthest_neighbor>3) {neighbor_distance[4] = std::sqrt(5.)*lattice_constant;}
        std::vector<Point> unit_cell(1, Eigen::Vector3d::Zero());
        return std::make_tuple(basis, neighbor_distance, unit_cell);
}

std::tuple<std::array<Point,2>, std::vector<double>, std::vector<Point> > make_triang(double lattice_constant, std::size_t furthest_neighbor, TRIANG_TYPE tt=TRIANG_TYPE::XC) {
        assert(furthest_neighbor <= 3);
        Eigen::Matrix3d rot;
        rot = Eigen::AngleAxisd(M_PI/3., Eigen::Vector3d::UnitZ());
        std::array<Point,2> basis;
        if (tt == TRIANG_TYPE::XC) {
                basis = {lattice_constant * Eigen::Vector3d::UnitX(), lattice_constant * (rot*Eigen::Vector3d::UnitX())};
        }
        else /*YC*/{
                basis = {lattice_constant * (rot.transpose()*Eigen::Vector3d::UnitY()), lattice_constant * Eigen::Vector3d::UnitY()};
        }
        std::vector<double> neighbor_distance(furthest_neighbor+1);
        neighbor_distance[0] = 0.;
        if (furthest_neighbor>0) {neighbor_distance[0] = lattice_constant;}
        if (furthest_neighbor>1) {neighbor_distance[1] = std::sqrt(3.)*lattice_constant;}
        if (furthest_neighbor>2) {neighbor_distance[2] = 2.*lattice_constant;}
        std::vector<Point> unit_cell(1, Eigen::Vector3d::Zero());
        return std::make_tuple(basis, neighbor_distance, unit_cell);
}
}
#endif
