#ifndef LAT_DRAWING_H_
#define LAT_DRAWING_H_

#include "util/Normalization.h"
#include "shapes/Polygon.h"
#include "shapes/Cube.h"
#include "shapes/Arrow.h"
#include "vivid/vivid.h"

namespace Lattice {
        template<typename Lattice>
        void drawVertices(Lattice& lat, const std::size_t a, Eigen::Matrix<double,Eigen::Dynamic,3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C)
        {
                assert(lat.colors_v[a].size()==0 or lat.colors_v[a].size()==lat.size() or lat.colors_v[a].size()==1);
                //draw black vertices if color is not given.
                if (lat.colors_v[a].size() == 0) {lat.colors_v[a].resize(lat.size()); std::fill(lat.colors_v[a].begin(),lat.colors_v[a].end(),vivid::Color("black"));}
                if (lat.colors_v[a].size() == 1) {auto c = lat.colors_v[a][0]; lat.colors_v[a].resize(lat.size()); std::fill(lat.colors_v[a].begin(),lat.colors_v[a].end(),c);}

                std::vector<Cube> cs;
                for (int ix=0; ix<lat.Lx; ix++)
                for (int iy=0; iy<lat.Ly; iy++) {
                        cs.push_back(Cube(lat.site_diameter,lat.site(ix,iy,a),lat.colors_v[a][lat.index.at(std::make_pair(ix,iy))]));
                }

                std::for_each(cs.begin(), cs.end(), [&V,&F,&C] (const Cube& c) {c.draw(V,F,C);});
                // lat.draw_vertices(a,V,F,C);
        }

        template<typename Lattice>
        void drawEdges(Lattice& lat, const std::size_t a, const std::size_t b,
                       Eigen::Matrix<double,Eigen::Dynamic,3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C)
        {
                assert(lat.start.size() == lat.end.size());

                assert(lat.colors_e[a][b].size()==0 or lat.colors_e[a][b].size()==lat.start.size() or lat.colors_e[a][b].size()==1);
                //draw black edges if color is not given.
                if (lat.colors_e[a][b].size() == 0) {
                        lat.colors_e[a][b].resize(lat.start.size()); std::fill(lat.colors_e[a][b].begin(),lat.colors_e[a][b].end(),vivid::Color("black"));}
                if (lat.colors_e[a][b].size() == 1) {
                        auto c = lat.colors_e[a][b][0]; lat.colors_e[a][b].resize(lat.start.size()); std::fill(lat.colors_e[a][b].begin(),lat.colors_e[a][b].end(),c);
                }

                std::vector<Tube> ts;
				for(std::size_t dist = 0; dist < lat.neighbors.size(); ++dist) {
					for(int ix = 0; ix < lat.Lx; ix++) {
						for(int iy = 0; iy < lat.Ly; iy++) {
							for(std::size_t num = 0; num < lat.neighbors[dist][lat.site_number(ix, iy, a)].size(); ++num) {
								auto [jx, jy, bp] = lat.neighbors[dist][lat.site_number(ix, iy, a)][num];
								if(bp != b) { continue; }
								ts.push_back(Tube(lat.bond_diameter, lat.site(ix, iy, a), lat.site(jx, jy, b), lat.colors_e[a][b][0]));
							}
						}
					}
				}
				std::cout << "#tubes: " << ts.size() << std::endl;
                std::for_each(ts.begin(), ts.end(), [&V,&F,&C] (const Tube& t) {t.draw(V,F,C);});
        }


        // template<typename Molecule>
        // void drawEdges(Molecule& mol, Eigen::Matrix<double,Eigen::Dynamic,3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C)
        // {
        //         assert(mol.colors_e.size()==0 or mol.colors_e.size()==mol.edges.size() or mol.colors_e.size()==1);
        //         //draw black vertices if color is not given.
        //         if (mol.colors_e.size() == 0) {mol.colors_e.resize(mol.edges.size()); std::fill(mol.colors_e.begin(),mol.colors_e.end(),vivid::Color("black"));}
        //         //set constant color if one color is given.
        //         if (mol.colors_e.size() == 1) {auto c = mol.colors_e[0]; mol.colors_e.resize(mol.colors_e.size()); std::fill(mol.colors_e.begin(),mol.colors_e.end(),c);}

        //         std::vector<std::array<Point,2> > edges_points(mol.edges.size());
        //         for (std::size_t j=0; j<mol.edges.size(); j++) {
        //                 Point start(mol.vertices[mol.schlegel_map.at(mol.edges[j][0])].data());
        //                 Point end(mol.vertices[mol.schlegel_map.at(mol.edges[j][1])].data());
        //                 edges_points[j][0] = start;
        //                 edges_points[j][1] = end;
        //         }

        //         std::vector<Tube> ts;
        //         for (std::size_t i=0; i<mol.edges.size(); i++) {
        //                 ts.push_back(Tube(mol.edge_diameter,edges_points[i][0],edges_points[i][1],mol.colors_e[i]));
        //         }
        //         std::for_each(ts.begin(), ts.end(), [&V,&F,&C] (const Tube& t) {t.draw(V,F,C);});
        // }

        template<typename Lattice>
        void plotSiteObs(Lattice& lat, const Eigen::VectorXi& pos, const Eigen::VectorXd& obs,
                         Eigen::Matrix<double,Eigen::Dynamic,3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C,
                         const util::Normalization& norm, const vivid::ColorMap::Preset map_in=vivid::ColorMap::Preset::Turbo, std::size_t a=0) {
                assert(obs.size() == lat.size() and pos.size() == obs.size() and "No valid data for site observable.");
                
                std::vector<vivid::Color> colv(lat.size());
                vivid::ColorMap map(map_in);

                for (std::size_t i=0; i<lat.size(); i++) {
                        colv[pos(i)] = map.at(norm(obs(i)));
                }
                lat.colors_v[a] = colv;
                drawVertices(lat,a,V,F,C);
        }

	template <typename Lattice>
void plotVecSiteObs(Lattice& lat,
                    const std::array<Eigen::VectorXd, 3>& obs,
                    Eigen::Matrix<double, Eigen::Dynamic, 3>& V,
                    Eigen::Matrix<int, Eigen::Dynamic, 3>& F,
                    Eigen::Matrix<double, Eigen::Dynamic, 3>& C,
                    std::size_t a = 0,
                    double length_scale_f = 1.)
{
    assert(obs[0].size() == lat.size() and pos.size() == obs[0].size() and "No valid data for site observable.");

    assert(lat.colors_v[a].size() == 0 or lat.colors_v[a].size() == lat.size() or lat.colors_v[a].size() == 1);
    // draw black vertices if color is not given.
    if(lat.colors_v[a].size() == 0) {
        lat.colors_v[a].resize(lat.size());
        std::fill(lat.colors_v[a].begin(), lat.colors_v[a].end(), vivid::Color("black"));
    }
    if(lat.colors_v[a].size() == 1) {
        auto c = lat.colors_v[a][0];
        lat.colors_v[a].resize(lat.size());
        std::fill(lat.colors_v[a].begin(), lat.colors_v[a].end(), c);
    }

    std::vector<Arrow> arrs;
    if constexpr(Lattice::dim == 2) {
        for(int ix = 0; ix < lat.Lx; ix++) {
            for(int iy = 0; iy < lat.Ly; iy++) {
                auto i = lat.site_number(ix, iy, a);
                Eigen::Vector3d mag;
                mag << obs[0](i), obs[1](i), obs[2](i);
                auto length = mag.norm();
                Eigen::Vector3d mag_normalized = mag / length;
                Eigen::Vector3d axis = Eigen::Vector3d::UnitZ().cross(mag_normalized);
                axis /= axis.norm();

                double angle = std::acos(Eigen::Vector3d::UnitZ().dot(mag_normalized));
                arrs.push_back(Arrow(/*height=*/length_scale_f * length,
                                     /*radius=*/0.03,
                                     /*radius_hat=*/0.06,
                                     /*ratio hat/cylinder*/ 0.3,
                                     /*axis*/ axis,
                                     /*angle*/ angle,
                                     lat.site(ix, iy, a),
                                     lat.colors_v[a][lat.index.at(std::make_pair(ix, iy))]));
            }
        }
    } else if constexpr(Lattice::dim == 3) {
        for(int ix = 0; ix < lat.Lx; ix++) {
            for(int iy = 0; iy < lat.Ly; iy++) {
                for(int iz = 0; iz < lat.Lz; iz++) {
                    int random_variable = std::rand();
                    double random_angle = static_cast<double>(random_variable) / static_cast<double>(RAND_MAX) * M_PI;
                    arrs.push_back(Arrow(0.3,
                                         0.03,
                                         0.06,
                                         0.3,
                                         Eigen::Vector3d::UnitX(),
                                         random_angle,
                                         lat.site(ix, iy, iz, a),
                                         lat.colors_v[a][lat.index.at(std::make_tuple(ix, iy, iz))]));
                }
            }
        }
    }
    std::for_each(arrs.begin(), arrs.end(), [&V, &F, &C](const Arrow& arr) { arr.draw(V, F, C); });
}

        template<typename Lattice>
        void plotBondObs(Lattice& lat, const Eigen::VectorXi& start, const Eigen::VectorXi& end, const Eigen::VectorXd& obs,
                         Eigen::Matrix<double,Eigen::Dynamic,3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C,
                         const util::Normalization& norm, const vivid::ColorMap::Preset map_in=vivid::ColorMap::Preset::Turbo,
                         std::size_t a=0, std::size_t b=0) {                
                assert(start.size() == obs.size() and end.size() == obs.size() and "No valid data for site observable.");

                lat.start = start;
                lat.end = end;
                
                std::vector<vivid::Color> colv(start.size());
                // util::Normalization norm(obs.minCoeff(),obs.maxCoeff());
                vivid::ColorMap map(map_in);

                for (std::size_t i=0; i<start.size(); i++) {
                        colv[i] = map.at(norm(obs(i)));
                }
                lat.colors_e[a][b] = colv;
                drawEdges(lat,a,b,V,F,C);
        }
}
#endif
