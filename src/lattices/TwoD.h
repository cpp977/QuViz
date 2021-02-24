#ifndef TWOD_H_
#define TWOD_H_

#include <vector>
#include <map>
#include <numeric>

#include "GlobalTypedefs.h"
#include "shapes/Tube.h"
#include "shapes/Cube.h"

namespace Lattice{
        
enum class TRAVERSE2D {CHESSBOARD, SNAKE};

class TwoD
{
public:
        TwoD() {}
        
        TwoD(const std::size_t Lx_in, const std::size_t Ly_in, const std::array<Point,2>& basis_in, const std::vector<double>& neighbor_distance_in)
                : Lx(Lx_in), Ly(Ly_in), atoms_per_cell(1), basis(basis_in), neighbor_distance(neighbor_distance_in) {
                unit_cell.push_back(Eigen::Vector3d::Zero());
                colors_v.resize(1);
                colors_e.resize(1);
                colors_e[0].resize(1);
                initialize_neighbors();
                initialize_numbering();
        }

        TwoD(const std::size_t Lx_in, const std::size_t Ly_in, const std::array<Point,2>& basis_in,
                  const std::vector<double>& neighbor_distance_in, const std::vector<Point> unit_cell_in, const std::function<std::array<int,2> (int, int)>& func)
                : Lx(Lx_in), Ly(Ly_in), atoms_per_cell(unit_cell_in.size()), basis(basis_in), unit_cell(unit_cell_in), neighbor_distance(neighbor_distance_in), boundary_func(func) {
                colors_v.resize(unit_cell.size());
                colors_e.resize(unit_cell.size());
                for (std::size_t a=0; a<unit_cell.size(); a++) {colors_e[a].resize(unit_cell.size());}
                
                initialize_neighbors();
                initialize_numbering();
        }

        std::size_t size() const {return Lx*Ly;}

        void draw(const std::function<bool (std::size_t, std::size_t, std::size_t)>& mask,
                  Eigen::Matrix<double,Eigen::Dynamic,3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const;

        void draw(Eigen::Matrix<double,Eigen::Dynamic,3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const {
                draw([](std::size_t a, std::size_t b, std::size_t distance) {return true;}, V,F,C);
        }

        bool ARE_NEIGHBORS(const Point& p1, const Point& p2, std::size_t range=1) const;

        Point site(const int ix, const int iy, const std::size_t a=0) const;
        
        double site_diameter = 0.12;
        double bond_diameter = 0.02;

        bool draw_bonds(std::size_t a, std::size_t b) const {
                if (a!=b) return true;
                if (a==0) return true;
                return false;
        }

        std::vector<std::vector<vivid::Color> > colors_v; //colors_v[cell][site]
        std::vector<std::vector<std::vector<vivid::Color> > > colors_e; //colors_v[cell1][cell2][bond]

        TRAVERSE2D path = TRAVERSE2D::SNAKE;

        Eigen::VectorXi start,end;
        
        //private:
        static constexpr std::size_t dim=2;
        std::size_t Lx, Ly;
        std::size_t atoms_per_cell;
        std::array<Point,2> basis;
        std::vector<Point> unit_cell;

        std::vector<double> neighbor_distance;
        std::vector<std::vector<std::vector<std::tuple<int,int,std::size_t> > > > neighbors;

        std::function<std::array<int,2> (int, int)> boundary_func;

        std::map<std::pair<int,int>,int> index;
	std::map<int,std::pair<int,int>> coord;
        
        void initialize_neighbors();
        void initialize_numbering();
        
        int site_number(const int ix, const int iy, const std::size_t a=0) const;
};

}
#endif
