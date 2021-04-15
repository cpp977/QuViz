#include <cstdint>
#include <algorithm>
#include <iostream>

#include <igl/writeSTL.h>

#include "IO/Io.h"

#include "shapes/Tube.h"
#include "shapes/Sphere.h"

#include "molecules/C60.h"
#include "molecules/SOD20.h"
#include "molecules/Drawing.h"

Eigen::Matrix<double,Eigen::Dynamic,3> V;
Eigen::Matrix<int,Eigen::Dynamic,3> F;
Eigen::Matrix<double,Eigen::Dynamic,3> C;

int main(int argc, char *argv[])
{
        // C60 mol;
        SOD20 mol;
        mol.colors_f.resize(30);
        for (std::size_t i=0; i<30; i++) {
                mol.colors_f[i] = (i<6) ? vivid::Color("grey") : vivid::Color("blue");
        }
        // auto [pos1,obs1] = IO::loadSiteObs(example_data+"/C60_triplet_S.dat");
        // auto [start, end, Scorr] = IO::loadBondObs(example_data+"/C60_triplet_Scorr.dat");
        // Mol::plotSiteObs(mol,pos1,obs1,V,F,C,vivid::ColorMap::Preset::Viridis);
        // Mol::plotBondObs(mol,start,end,Scorr,V,F,C);
        Mol::drawVertices(mol,V,F,C);
        Mol::drawFaces(mol,V,F,C);

        std::cout << V.rows() << ", " << F.rows() << ", " << C.rows() << std::endl;

        // Export the mesh to stl
        igl::writeSTL(mol.name()+".stl", V, F);
}
