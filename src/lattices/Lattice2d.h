#ifndef LATTICE2D_H_
#define LATTICE2D_H_

#include <vector>
#include <unordered_map>

#include "GlobalTypedefs.h"
#include "shapes/Tube.h"
#include "shapes/Cube.h"

class Lattice2d
{
public:
        Lattice2d() {}
        
        Lattice2d(const std::size_t Lx_in, const std::size_t Ly_in, const std::array<Point,2>& basis_in, const std::vector<double>& neighbor_distance_in)
                : Lx(Lx_in), Ly(Ly_in), atoms_per_cell(1), basis(basis_in), neighbor_distance(neighbor_distance_in) {
                unit_cell.push_back(Eigen::Vector3d::Zero());
                colors_v.resize(1);
                initialize_neighbors();
        }

        Lattice2d(const std::size_t Lx_in, const std::size_t Ly_in, const std::array<Point,2>& basis_in,
                  const std::vector<double>& neighbor_distance_in, const std::vector<Point> unit_cell_in, const std::function<std::array<int,2> (int, int)>& func)
                : Lx(Lx_in), Ly(Ly_in), atoms_per_cell(unit_cell_in.size()), basis(basis_in), unit_cell(unit_cell_in), neighbor_distance(neighbor_distance_in), boundary_func(func) {
                colors_v.resize(unit_cell.size());
                initialize_neighbors();
        }

        std::size_t size() const {return Lx*Ly;}

        void draw(const std::function<bool (std::size_t, std::size_t, std::size_t)>& draw_bonds,
                  Eigen::Matrix<double,Eigen::Dynamic,3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const;

        void draw(Eigen::Matrix<double,Eigen::Dynamic,3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const {
                draw([](std::size_t a, std::size_t b, std::size_t distance) {return true;}, V,F,C);
        }

        bool ARE_NEIGHBORS(const Point& p1, const Point& p2, std::size_t range=1) const;

        Point site(const int ix, const int iy, const std::size_t a=0) const;
        
        double site_diameter = 0.1;
        double bond_diameter = 0.01;

        bool draw_bonds(std::size_t a, std::size_t b) const {
                if (a!=b) return true;
                if (a==0) return true;
                return false;
        }

        std::vector<std::vector<vivid::Color> > colors_v;
        std::vector<std::vector<vivid::Color> > colors_e;
private:
        static constexpr std::size_t dim=2;
        std::size_t Lx, Ly;
        std::size_t atoms_per_cell;
        std::array<Point,2> basis;
        std::vector<Point> unit_cell;

        std::vector<double> neighbor_distance;
        std::vector<std::vector<std::vector<std::tuple<int,int,std::size_t> > > > neighbors;

        std::function<std::array<int,2> (int, int)> boundary_func;

        void initialize_neighbors();
        
        int site_number(const int ix, const int iy, const std::size_t a=0) const;
};

#endif
/* double a=0.2; */
        /* double b=0.05; */
        /* double c=1.; */

// auto unitX = Eigen::Vector3d::UnitX();
        // auto unitY = Eigen::Vector3d::UnitY();
        // auto unitZ = Eigen::Vector3d::UnitZ();

// std::size_t Lx=12;
        // std::size_t Ly=6;

        // std::vector<Cube> cs;
        // for (std::size_t ix=0; ix<Lx; ix++) {
        //         for (std::size_t iy=0; iy<Ly; iy++) {
        //                 // sps.push_back(Sphere(a,ix*unitX+iy*unitY,Palette::blue));
        //                 // sps.push_back(Sphere(a,ix*unitX+iy*unitY+c*unitZ,Palette::orange));
        //                 cs.push_back(Cube(a,ix*unitX+iy*unitY,Palette::blue));
        //                 cs.push_back(Cube(a,ix*unitX+iy*unitY+c*unitZ,Palette::orange));
        //         }
        // }
        // std::vector<Tube> ts;
        // for (std::size_t ix=0; ix<Lx; ix++) {
        //         for (std::size_t iy=0; iy<Ly; iy++) {
        //                 if (ix<Lx-1) ts.push_back(Tube(b,ix*unitX+iy*unitY,(ix+1)*unitX+iy*unitY,Palette::black));
        //                 if (iy<Ly-1) ts.push_back(Tube(b,ix*unitX+iy*unitY,ix*unitX+(iy+1)*unitY,Palette::black));
        //                 if (ix>0 and iy<Ly-1) ts.push_back(Tube(b,ix*unitX+iy*unitY,(ix-1)*unitX+(iy+1)*unitY,Palette::black));
        //                 // if (ix<Lx-1) ts.push_back(Tube(b,ix*unitX+iy*unitY+c*unitZ,(ix+1)*unitX+iy*unitY+c*unitZ,Palette::black));
        //                 // if (iy<Ly-1) ts.push_back(Tube(b,ix*unitX+iy*unitY+c*unitZ,ix*unitX+(iy+1)*unitY+c*unitZ,Palette::black));
        //                 // if (ix>0 and iy<Ly-1) ts.push_back(Tube(b,ix*unitX+iy*unitY+c*unitZ,(ix-1)*unitX+(iy+1)*unitY+c*unitZ,Palette::black));
        //                 ts.push_back(Tube(b,ix*unitX+iy*unitY,ix*unitX+(iy)*unitY+c*unitZ,Palette::black));
        //         }
        // }
        // std::for_each(sps.begin(), sps.end(), [] (const Sphere& s) {s.draw(V,F,C);});
        // std::for_each(cs.begin(), cs.end(), [] (const Cube& c) {c.draw(V,F,C);});
        // std::for_each(ts.begin(), ts.end(), [] (const Tube& t) {t.draw(V,F,C);});
