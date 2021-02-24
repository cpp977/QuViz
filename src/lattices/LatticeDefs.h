#ifndef LATTICE_DEFS_H_
#define LATTICE_DEFS_H_

#include "Eigen/Dense"
#include "Eigen/Geometry"

#include "GlobalTypedefs.h"
#include "lattices/TwoD.h"

namespace Lattice {

enum class TRIANG_TYPE {
        NORMAL=0,
        XC=1,
        YC=2
};
        
TwoD make_square(const std::size_t Lx, const std::size_t Ly, double lattice_constant, std::size_t furthest_neighbor=1) {
        assert(furthest_neighbor <= 4);
        std::array<Point,2> basis = {lattice_constant * Eigen::Vector3d::UnitX(), lattice_constant * Eigen::Vector3d::UnitY()};
        std::vector<double> neighbor_distance(furthest_neighbor);
        if (furthest_neighbor>0) {neighbor_distance[0] = lattice_constant;}
        if (furthest_neighbor>1) {neighbor_distance[1] = std::sqrt(2.)*lattice_constant;}
        if (furthest_neighbor>2) {neighbor_distance[2] = 2.*lattice_constant;}
        if (furthest_neighbor>3) {neighbor_distance[3] = std::sqrt(5.)*lattice_constant;}
        std::vector<Point> unit_cell(1, Eigen::Vector3d::Zero());
        return TwoD(Lx, Ly, basis, neighbor_distance, unit_cell, [] (int ix, int iy) {return std::array<int,2>{ix, iy};});
}

TwoD make_triang(const std::size_t Lx, const std::size_t Ly, double lattice_constant, TRIANG_TYPE tt=TRIANG_TYPE::XC, std::size_t furthest_neighbor=1) {
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
        std::vector<double> neighbor_distance(furthest_neighbor);
        if (furthest_neighbor>0) {neighbor_distance[0] = lattice_constant;}
        if (furthest_neighbor>1) {neighbor_distance[1] = std::sqrt(3.)*lattice_constant;}
        if (furthest_neighbor>2) {neighbor_distance[2] = 2.*lattice_constant;}

        std::vector<Point> unit_cell(1, Eigen::Vector3d::Zero());
        if (tt == TRIANG_TYPE::YC) {
                return TwoD(Lx, Ly, basis, neighbor_distance, unit_cell, [] (int ix, int iy) {return std::array<int,2>{ix, iy-static_cast<int>(std::floor(static_cast<double>(ix)/2.))};});
        }
        else if (tt == TRIANG_TYPE::XC) {
                return TwoD(Lx, Ly, basis, neighbor_distance, unit_cell, [] (int ix, int iy) {return std::array<int,2>{ix-static_cast<int>(std::floor(static_cast<double>(iy)/2.)), iy};});
        }
        return TwoD(Lx, Ly, basis, neighbor_distance, unit_cell, [] (int ix, int iy) {return std::array<int,2>{ix, iy};});
}

TwoD make_kondo_square(const std::size_t Lx, const std::size_t Ly, double lattice_constant, double kondo_lattice_constant, std::size_t furthest_neighbor=1) {
        assert(furthest_neighbor <= 1);
        std::array<Point,2> basis = {lattice_constant * Eigen::Vector3d::UnitX(), lattice_constant * Eigen::Vector3d::UnitY()};
        std::vector<double> neighbor_distance(furthest_neighbor);
        if (furthest_neighbor>0) {
                neighbor_distance[0] = (kondo_lattice_constant < lattice_constant) ? kondo_lattice_constant : lattice_constant;
                neighbor_distance[1] = (kondo_lattice_constant < lattice_constant) ? lattice_constant : kondo_lattice_constant;
        }
        std::vector<Point> unit_cell(1, Eigen::Vector3d::Zero());
        unit_cell.push_back(-kondo_lattice_constant*Eigen::Vector3d::UnitZ());
        return TwoD(Lx, Ly, basis, neighbor_distance, unit_cell, [] (int ix, int iy) {return std::array<int,2>{ix, iy};});
}
        
TwoD make_kondo_triang(const std::size_t Lx, const std::size_t Ly, double lattice_constant, double kondo_lattice_constant,
                       TRIANG_TYPE tt=TRIANG_TYPE::XC, std::size_t furthest_neighbor=1ul) {
        assert(furthest_neighbor <= 1);
        Eigen::Matrix3d rot;
        rot = Eigen::AngleAxisd(M_PI/3., Eigen::Vector3d::UnitZ());
        std::array<Point,2> basis;
        if (tt == TRIANG_TYPE::XC) {
                basis = {lattice_constant * Eigen::Vector3d::UnitX(), lattice_constant * (rot*Eigen::Vector3d::UnitX())};
        }
        else /*YC*/{
                basis = {lattice_constant * (rot.transpose()*Eigen::Vector3d::UnitY()), lattice_constant * Eigen::Vector3d::UnitY()};
        }
        std::vector<double> neighbor_distance(furthest_neighbor);
        if (furthest_neighbor>0) {
                neighbor_distance[0] = (kondo_lattice_constant < lattice_constant) ? kondo_lattice_constant : lattice_constant;
                neighbor_distance[1] = (kondo_lattice_constant < lattice_constant) ? lattice_constant : kondo_lattice_constant;
        }
        // if (furthest_neighbor>1) {neighbor_distance[1] = std::sqrt(3.)*lattice_constant;}
        // if (furthest_neighbor>2) {neighbor_distance[2] = 2.*lattice_constant;}
        std::vector<Point> unit_cell(1, Eigen::Vector3d::Zero());
        unit_cell.push_back(-kondo_lattice_constant*Eigen::Vector3d::UnitZ());
        if (tt == TRIANG_TYPE::YC) {
                return TwoD(Lx, Ly, basis, neighbor_distance, unit_cell, [] (int ix, int iy) {return std::array<int,2>{ix, iy-static_cast<int>(std::floor(static_cast<double>(ix)/2.))};});
        }
        else if (tt == TRIANG_TYPE::XC) {
                return TwoD(Lx, Ly, basis, neighbor_distance, unit_cell, [] (int ix, int iy) {return std::array<int,2>{ix-static_cast<int>(std::floor(static_cast<double>(iy)/2.)), iy};});
        }
        return TwoD(Lx, Ly, basis, neighbor_distance, unit_cell, [] (int ix, int iy) {return std::array<int,2>{ix, iy};});
}

}
#endif
