#include "lattices/Lattice2d.h"
#include <iostream>
Point Lattice2d::
site(const int ix, const int iy, const std::size_t a) const
{
        auto [ixp, iyp] = boundary_func(ix,iy);
        return ixp*basis[0]+iyp*basis[1] + unit_cell[a];
}

void Lattice2d::
draw(const std::function<bool (std::size_t, std::size_t, std::size_t)>& draw_bonds,
     Eigen::Matrix<double,Eigen::Dynamic,3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const
{        
        std::vector<Cube> cs;
        std::vector<Tube> ts;
        for (int ix=0; ix<Lx; ix++) {
                for (int iy=0; iy<Ly; iy++) {
                        for (int a=0; a<atoms_per_cell; a++) {
                                for (int distance=0; distance<neighbor_distance.size(); distance++) {
                                        for (const auto& [jx, jy, b] : neighbors[distance][site_number(ix,iy,a)]) {
                                                if (draw_bonds(a,b,distance)) {
                                                        if (distance == 0) cs.push_back(Cube(site_diameter,site(ix,iy,a),colors_v[a][iy*Lx+ix]));
                                                        else ts.push_back(Tube(bond_diameter,site(ix,iy,a),site(jx,jy,b),vivid::Color("blue")));
                                                }
                                        }
                                }
                        }
                }        
        }
        std::for_each(cs.begin(), cs.end(), [&V,&F,&C] (const Cube& c) {c.draw(V,F,C);});
        std::for_each(ts.begin(), ts.end(), [&V,&F,&C] (const Tube& t) {t.draw(V,F,C);});
}

int Lattice2d::
site_number(const int ix, const int iy, const std::size_t a) const
{
        return atoms_per_cell*(iy*Lx + ix) + a;
}

void Lattice2d::
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
                        if (ARE_NEIGHBORS(site(ix,iy,a), site(jx,jy,b), distance)) {neighbors[distance][site_number(ix,iy,a)].push_back(std::make_tuple(jx,jy,b));}
                }
        }
}

bool Lattice2d::
ARE_NEIGHBORS(const Point& p1, const Point& p2, std::size_t range) const
{
        assert(range < neighbor_distance.size());
        
	if (std::abs((p2 - p1).norm()-neighbor_distance[range]) < 1.e-6) {return true;}
        return false;
	// if (PERIODIC_Y and Ly > 2)
	// 	{
	// 		//shift R_i into the super cell above the current super cell
	// 		Point p1_upshift = p1 + Ly*basis[1];
	// 		double distance_upshift = (p1_upshift - p2).norm();
	// 		if (abs(distance_upshift-neighbor_distance[range-1]) < mynumeric_limits<double>::epsilon()) {return true;}

	// 		//shift R_i into the super cell below the current super cell
	// 		Point p1_downshift = p1 - Ly*basis[1];
	// 		double distance_downshift = (p1_downshift - p2).norm();
	// 		if (abs(distance_downshift-neighbor_distance[range-1]) < mynumeric_limits<double>::epsilon()) {return true;}
	// 	}
	// if (PERIODIC_X and Lx > 2)
	// 	{
	// 		//shift R_i into the super cell right of the current super cell
	// 		Point p1_rightshift = p1 + Lx*basis[0];
	// 		double distance_rightshift = (p1_rightshift - p2).norm();
	// 		if (abs(distance_rightshift-neighbor_distance[range-1]) < mynumeric_limits<double>::epsilon()) {return true;}

	// 		//shift R_i into the super cell left of the current super cell
	// 		Point p1_leftshift = p1 - Lx*basis[0];
	// 		double distance_leftshift = (p1_leftshift - p2).norm();
	// 		if (abs(distance_leftshift-neighbor_distance[range-1]) < mynumeric_limits<double>::epsilon()) {return true;}			
	// 	}
	// if ( (PERIODIC_X and Lx > 2) and (PERIODIC_Y and Ly > 2) )
	// 	{
	// 		//shift R_i into the super cell above and right of the current super cell
	// 		Point p1_ru_shift = p1 + Lx*basis[0]+Ly*basis[1];
	// 		double distance_ru_shift = (p1_ru_shift - p2).norm();
	// 		if (abs(distance_ru_shift-neighbor_distance[range-1]) < mynumeric_limits<double>::epsilon()) {return true;}

	// 		//shift R_i into the super cell above and left of the current super cell
	// 		Point p1_lu_shift = p1 - Lx*basis[0]+Ly*basis[1];
	// 		double distance_lu_shift = (p1_lu_shift - p2).norm();
	// 		if (abs(distance_lu_shift-neighbor_distance[range-1]) < mynumeric_limits<double>::epsilon()) {return true;}

	// 		//shift R_i into the super cell below and right of the current super cell
	// 		Point Ri_rb_shift = p1 + Lx*basis[0]-Ly*basis[1];
	// 		double distance_rb_shift = (p1_rb_shift - p2).norm();
	// 		if (abs(distance_rb_shift-neighbor_distance[range-1]) < mynumeric_limits<double>::epsilon()) {return true;}

	// 		//shift R_i into the super cell below and left of the current super cell
	// 		Point p1_lb_shift = p1 - Lx*basis[0]-Ly*basis[1];
	// 		double distance_lb_shift = (p1_lb_shift - p2).norm();
	// 		if (abs(distance_lb_shift-neighbor_distance[range-1]) < mynumeric_limits<double>::epsilon()) {return true;}
	// 	}
}

