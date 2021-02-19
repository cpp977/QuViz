#ifndef LAT_DRAWING_H_
#define LAT_DRAWING_H_

#include "util/Normalization.h"
#include "shapes/Polygon.h"
#include "vivid/vivid.h"

namespace Lattice {
        template<typename Lattice>
        void drawVertices(Lattice& lat, const std::size_t a, Eigen::Matrix<double,Eigen::Dynamic,3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C)
        {
                assert(lat.colors_v[a].size()==0 or lat.colors_v[a].size()==lat.size() or lat.colors_v[a].size()==1);
                //draw black vertices if color is not given.
                if (lat.colors_v[a].size() == 0) {lat.colors_v[a].resize(lat.size()); std::fill(lat.colors_v[a].begin(),lat.colors_v[a].end(),vivid::Color("black"));}
                if (lat.colors_v[a].size() == 1) {auto c = lat.colors_v[a][0]; lat.colors_v[a].resize(lat.size()); std::fill(lat.colors_v[a].begin(),lat.colors_v[a].end(),c);}

                lat.draw([&a](std::size_t b, std::size_t c, std::size_t distance) {if (b==a and c==a and distance==0) {return true;} return false;},V,F,C);
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

        // template<typename Molecule>
        // void plotSiteObs(Molecule& mol, const Eigen::VectorXi& pos, const Eigen::VectorXd& obs,
        //                  Eigen::Matrix<double,Eigen::Dynamic,3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C,
        //                  vivid::ColorMap::Preset map_in=vivid::ColorMap::Preset::Turbo) {
        //         assert(obs.size() == mol.vertices.size() and pos.size() == obs.size() and "No valid data for site observable");
                
        //         std::vector<vivid::Color> colv(mol.vertices.size());
        //         util::Normalization norm(obs.minCoeff(),obs.maxCoeff());
        //         vivid::ColorMap map(map_in);

        //         for (std::size_t i=0; i<mol.vertices.size(); i++) {
        //                 colv[pos(i)] = map.at(norm(obs(i)));
        //         }
        //         mol.colors_v = colv;
        //         drawVertices(mol,V,F,C);
        // }

        // template<typename Molecule>
        // void plotBondObs(Molecule& mol, const Eigen::VectorXi& start, const Eigen::VectorXi& end, const Eigen::VectorXd& obs,
        //                  Eigen::Matrix<double,Eigen::Dynamic,3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C,
        //                  vivid::ColorMap::Preset map_in=vivid::ColorMap::Preset::Turbo) {
        //         assert(obs.size() == mol.edges.size() and "No valid data for edge observable");
        //         assert(start.size() == mol.edges.size() and "No valid data for edge observable");
        //         assert(end.size() == mol.edges.size() and "No valid data for edge observable");
        //         for (std::size_t i=0; i<mol.edges.size(); i++) {
        //                 mol.edges[i][0] = start(i);
        //                 mol.edges[i][1] = end(i);
        //         }
        //         std::vector<vivid::Color> cole(mol.edges.size());
        //         util::Normalization norm(obs.minCoeff(),obs.maxCoeff());
        //         vivid::ColorMap map(map_in);
        //         for (std::size_t i=0; i<mol.edges.size(); i++) {
        //                 cole[i] = map.at(norm(obs(i)));
        //         }
        //         mol.colors_e = cole;
        //         drawEdges(mol,V,F,C);
        // }
}
#endif
