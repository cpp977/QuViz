#include <cstdint>
#include <algorithm>
#include <iostream>

#include <igl/png/render_to_png.h>
#include <igl/png/writePNG.h>
#include <igl/embree/EmbreeRenderer.h>

#include "util/Export.h"
#include "IO/Io.h"

#include "shapes/Tube.h"
#include "shapes/Sphere.h"

#include "molecules/C60.h"
#include "molecules/Drawing.h"

Eigen::Matrix<double,Eigen::Dynamic,3> V;
Eigen::Matrix<int,Eigen::Dynamic,3> F;
Eigen::Matrix<double,Eigen::Dynamic,3> C;

int main(int argc, char *argv[])
{
        std::string example_data = "/home/user/__LIBS__/QuViz/example-data";
        // C60 mol;
        SOD20 mol;
        // auto [pos1,obs1] = IO::loadSiteObs(example_data+"/C60_triplet_S.dat");
        // auto [start, end, Scorr] = IO::loadBondObs(example_data+"/C60_triplet_Scorr.dat");
        // Mol::plotSiteObs(mol,pos1,obs1,V,F,C,vivid::ColorMap::Preset::Viridis);
        // Mol::plotBondObs(mol,start,end,Scorr,V,F,C);
        // Mol::drawFaces(mol,V,F,C);
        Mol::drawVertices(mol,V,F,C);

        std::cout << V.rows() << ", " << F.rows() << ", " << C.rows() << std::endl;

        // Plot the mesh
        igl::embree::EmbreeRenderer er;
        er.set_mesh(V,F,true);
        er.set_colors(C);
        er.set_zoom(1.5);
        er.set_orthographic(false);
        Point translation; translation << 0.,0.,-0.5;
        er.set_translation(translation);

        FileFormats::PNGOptions pngOptions;
        Export::PNG("C60.png", pngOptions, 0., 1./std::sqrt(2.)*(Eigen::Vector3d::UnitY()+Eigen::Vector3d::UnitX()), er);
}
