#include <cstdint>
#include <algorithm>
#include <iostream>

#include <igl/stb/write_image.h>
#include <igl/embree/EmbreeRenderer.h>

#include "util/Export.h"
#include "IO/Io.h"

#include "shapes/Tube.h"
#include "shapes/Sphere.h"

#include "molecules/C60.h"
#include "molecules/SOD20.h"
#include "molecules/SOD60.h"
#include "molecules/Drawing.h"

Eigen::Matrix<double,Eigen::Dynamic,3> V;
Eigen::Matrix<int,Eigen::Dynamic,3> F;
Eigen::Matrix<double,Eigen::Dynamic,3> C;

int main(int argc, char* argv[])
{
    std::string example_data = "/home/user/__LIBS__/QuViz/example-data";
    C60 mol;
    auto [pos1, obs1] = IO::loadSiteObs(example_data + "/C60_triplet_S.dat");
    auto [start, end, Scorr] = IO::loadBondObs(example_data + "/C60_triplet_Scorr.dat");
    Mol::plotSiteObs(mol, pos1, obs1, V, F, C, vivid::ColorMap::Preset::Viridis);
    Mol::plotBondObs(mol, start, end, Scorr, V, F, C);
    Mol::drawFaces(mol, V, F, C);

    std::cout << V.rows() << ", " << F.rows() << ", " << C.rows() << std::endl;

    // Plot the mesh
    igl::embree::EmbreeRenderer er;
    er.set_mesh(V, F, true);
    er.set_colors(C);
    er.set_zoom(1.2);
    er.set_orthographic(false);
    Point translation;
    translation << 0., 0., -0.5;
    er.set_translation(translation);

    FileFormats::GifOptions gifOptions;
    gifOptions.framedelay = 5;
    gifOptions.loopcount = 2;
    Eigen::Vector3d axis = (std::sqrt(1. / 9.) * Eigen::Vector3d::UnitY() + std::sqrt(3. / 9.) * Eigen::Vector3d::UnitY() +
                            std::sqrt(5. / 9.) * Eigen::Vector3d::UnitZ());
    axis /= axis.norm();
    Export::GIF(mol.name() + ".gif", gifOptions, 100, axis, er);
}
