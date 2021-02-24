#include "lattices/TwoD.h"
#include <iostream>

namespace Lattice {
        
Point TwoD::
site(const int ix, const int iy, const std::size_t a) const
{
        auto [ixp, iyp] = boundary_func(ix,iy);
        return ixp*basis[0]+iyp*basis[1] + unit_cell[a];
}

void TwoD::
draw(const std::function<bool (std::size_t, std::size_t, std::size_t)>& mask,
     Eigen::Matrix<double,Eigen::Dynamic,3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const
{
        // draw_vertices(V,F,C);
        // draw_edges(V,F,C);
}
        
// void TwoD::
// draw_vertices(const std::size_t a,
//      Eigen::Matrix<double,Eigen::Dynamic,3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const
// {        
//         std::vector<Cube> cs;
//         for (int ix=0; ix<Lx; ix++)
//         for (int iy=0; iy<Ly; iy++) {
//                 cs.push_back(Cube(site_diameter,site(ix,iy,a),colors_v[a][index.at(std::make_pair(ix,iy))]));
//         }

//         std::for_each(cs.begin(), cs.end(), [&V,&F,&C] (const Cube& c) {c.draw(V,F,C);});
// }

// void TwoD::
// draw_edges(const std::size_t a, const std::size_t b,
//      Eigen::Matrix<double,Eigen::Dynamic,3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const
// {
//         std::vector<Tube> ts;
//         for (std::size_t edge=0; edge<edges.size(); edge++) {
//                 auto [ix,iy] = coord(start(edge));
//                 auto [jx,jy] = coord(end(edge));
//                 ts.push_back(Tube(bond_diameter,site(ix,iy,a),site(jx,jy,b),colors_e_inter[a][b][edge]));
//         }
//         // for (int ix=0; ix<Lx; ix++)
//         // for (int iy=0; iy<Ly; iy++)
//         // for (int a=0; a<atoms_per_cell; a++)
//         // for (int distance=0; distance<neighbor_distance.size(); distance++)
//         // for (const auto& [jx, jy, b] : neighbors[distance][site_number(ix,iy,a)]) {
//         //         if (mask(a,b,distance)) {
//         //                 if (ix == jx and iy == jy) /*intra cell*/ {
//         //                         ts.push_back(Tube(bond_diameter,site(ix,iy,a),site(jx,jy,b),colors_e_intra[a][b][index.at(std::make_pair(ix,iy))]));
//         //                 }
//         //                 else /*inter cell*/ {
//         //                         num_i = index.at(std::make_pair(ix,iy));
//         //                         num_j = index.at(std::make_pair(jx,jy));
//         //                         ts.push_back(Tube(bond_diameter,site(ix,iy,a),site(jx,jy,b),colors_e_inter[a][b][index.at(std::make_pair(ix,iy))]));
//         //                 }
//         //         }
//         // }

//         std::for_each(ts.begin(), ts.end(), [&V,&F,&C] (const Tube& t) {t.draw(V,F,C);});
// }
        
int TwoD::
site_number(const int ix, const int iy, const std::size_t a) const
{
        return atoms_per_cell*(iy*Lx + ix) + a;
}

void TwoD::
initialize_neighbors()
{
        neighbors.resize(neighbor_distance.size());
        for (std::size_t distance=0; distance<neighbor_distance.size(); distance++)  {
                neighbors[distance].resize(Lx*Ly*atoms_per_cell);
        
                for (int ix=0; ix<Lx; ix++) 
                for (int iy=0; iy<Ly; iy++) 
                for (std::size_t a=0; a<atoms_per_cell; a++) 
                for (int jx=0; jx<Lx; jx++) 
                for (int jy=0; jy<Ly; jy++) 
                for (std::size_t b=0; b<atoms_per_cell; b++) {
                        if (ARE_NEIGHBORS(site(ix,iy,a), site(jx,jy,b), distance+1)) {neighbors[distance][site_number(ix,iy,a)].push_back(std::make_tuple(jx,jy,b));}
                }
        }
}

void TwoD::
initialize_numbering()
{
        // Mirrors the y coordinate to create a snake.
	auto mirror = [this] (int iy) -> int
	{
                std::vector<int> v(Ly);
		std::iota(std::begin(v),std::end(v),0);
                std::reverse(v.begin(),v.end());
		return v[iy];
	};
        
        for (int ix=0; ix<Lx; ++ix)
	for (int iy=0; iy<Ly; ++iy)
	{
                int iy_=iy;
                if (path == TRAVERSE2D::SNAKE) {
                        // mirror even y only
                        iy_ = (ix%2==0)? iy : mirror(iy);
                }
                // the index is calculated normally:
                int index_i = iy + Ly*ix;
		
                // but is stored together with the mirrored y_:
                index[std::make_pair(ix,iy_)] = index_i;
                coord[index_i] = std::make_pair(ix,iy_);
                // std::cout << "ix=" << ix << ", iy_=" << iy_ << ", index_i=" << index_i << std::endl;
        }
}
        
bool TwoD::
ARE_NEIGHBORS(const Point& p1, const Point& p2, std::size_t range) const
{
        assert(range-1 < neighbor_distance.size());
        
	if (std::abs((p2 - p1).norm()-neighbor_distance[range-1]) < 1.e-6) {return true;}
        return false;
}

}
