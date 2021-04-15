#include <algorithm>
#include <cstdint>
#include <iostream>

#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/imgui/ImGuiHelpers.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/png/render_to_png.h>
#include <igl/png/writePNG.h>
#include <imgui/imgui.h>

#include "fonts/Digital.h"
#include "render/TextRenderer.h"

#include "IO/Io.h"
int file_id = 0;
#include "vivid/vivid.h"

#include "util/ColorLegend.h"

// #include "lattices/TwoD.h"
// #include "lattices/LatticeDefs.h"
// #include "lattices/Drawing.h"

#include "molecules/C60.h"
#include "molecules/Drawing.h"

bool key_down(igl::opengl::glfw::Viewer& viewer, unsigned char key, int modifier)
{
    if(key == '1') {
        // Allocate temporary buffers
        Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> R(1280, 800);
        Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> G(1280, 800);
        Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> B(1280, 800);
        Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> A(1280, 800);

        // Draw the scene in the buffers
        viewer.core().draw_buffer(viewer.data(), false, R, G, B, A);

        // Save it to a PNG
        std::stringstream ss;
        ss << "C60_" << file_id << ".png";
        file_id++;
        igl::png::writePNG(R, G, B, A, ss.str());
    } else if(key == '2') {
        Eigen::Matrix3f rot;
        rot = Eigen::AngleAxisf(0.01 * M_PI, Eigen::Vector3f::UnitZ());
        viewer.core().camera_up = rot * viewer.core().camera_up;
        std::cout << viewer.core().camera_up.transpose() << std::endl;
    } else if(key == '3') {
        Eigen::Matrix3f rot;
        rot = Eigen::AngleAxisf(0.01 * M_PI, Eigen::Vector3f::UnitZ());
        viewer.core().camera_up = rot.transpose() * viewer.core().camera_up;
        std::cout << viewer.core().camera_up.transpose() << std::endl;
    } else if(key == '4') {
        viewer.core().camera_zoom *= 1.01;
        std::cout << viewer.core().camera_zoom << std::endl;
    } else if(key == '5') {
        viewer.core().camera_zoom *= 0.99;
        std::cout << viewer.core().camera_zoom << std::endl;
    } else if(key == '6') {
        viewer.core().camera_view_angle *= 2.;
        std::cout << viewer.core().camera_view_angle << std::endl;
    } else if(key == '7') {
        viewer.core().camera_view_angle *= 0.5;
        std::cout << viewer.core().camera_view_angle << std::endl;
    }
    return false;
}

Eigen::Matrix<double,Eigen::Dynamic,3> V;
Eigen::Matrix<int,Eigen::Dynamic,3> F;
Eigen::Matrix<double,Eigen::Dynamic,3> C;

int main(int argc, char* argv[])
{
    // int U = std::stoi(argv[1]);
    // int M = std::stoi(argv[2]);
    // std::cout << "U=" << U << std::endl;
    // std::cout << "M=" << M << std::endl;
    double b = 0.8;
    double c = 0.6;

    std::string example_data = "/home/user/__LIBS__/QuViz/example-data";

    std::string base_path = "/home/user/cluster-calcHUBB/FULLERENE/502";
    // std::stringstream filename;
    std::string filename = argv[1];
    std::string TWO_SITE_ = "false";
    if(argc > 2) TWO_SITE_ = argv[2];
    bool TWO_SITE = true;
    if(TWO_SITE_ == "false" or TWO_SITE_ == "False" or TWO_SITE_ == "f" or TWO_SITE_ == "0") TWO_SITE = false;
    std::cout << "Plotting file " << filename << std::endl;
    // filename << "n_L=60_N=60_S=0_U=" << U << "_MOL=C60CMK_Mlimit=" << M << ".dat";
    std::size_t Lx = 12;
    std::size_t Ly = 6;

    // Lattice::TwoD triang = Lattice::make_kondo_triang(Lx,Ly,b,c,Lattice::TRIANG_TYPE::YC);

    // IO::LoadInfos li(IO::LOAD_MODE::HDF5, "Sz", "5000");
    // auto [pos0, obs0] =
    // IO::loadSiteObs("/home/user/__LIBS__/QuViz/src/examples/viewer/Lx=12_Ly=6_Jxy=1_Jz=1_Jkxy=0.5_Jkz=0.5_Ixy=0_Iz=0.4_triangularYC_periodicY.h5",li);
    // li.obsname = "sz";
    // auto [pos1, obs1] =
    // IO::loadSiteObs("/home/user/__LIBS__/QuViz/src/examples/viewer/Lx=12_Ly=6_Jxy=1_Jz=1_Jkxy=0.5_Jkz=0.5_Ixy=0_Iz=0.4_triangularYC_periodicY.h5",li);

    // li.obsname = "n_SdagS";
    // auto [start, end, corr] = IO::loadBondObs(example_data+"/KNM_12_6.h5",li);

    // li.obsname = "kondo";
    // auto [startK, endK, corrK] =
    // IO::loadBondObs("/home/user/__LIBS__/QuViz/src/examples/viewer/Lx=12_Ly=6_Jxy=1_Jz=1_Jkxy=0.5_Jkz=0.5_Ixy=0_Iz=0.4_triangularYC_periodicY.h5",li);

    // li.obsname = "n_sdags";
    // auto [starte, ende, corre] =
    // IO::loadBondObs("/home/user/__LIBS__/QuViz/src/examples/viewer/Lx=12_Ly=6_Jxy=1_Jz=1_Jkxy=0.5_Jkz=0.5_Ixy=0_Iz=0.4_triangularYC_periodicY.h5",li);

    // double min = corr.minCoeff();//std::min({corre.minCoeff(),corr.minCoeff(),corrK.minCoeff()});
    // double max = corr.maxCoeff();//std::max({corre.maxCoeff(),corr.maxCoeff(),corrK.maxCoeff()});
    // util::color_legend(9*Eigen::Vector3d::UnitX(), vivid::ColorMap::Preset::Turbo, min, max, V, F, C);
    // Lattice::plotSiteObs(triang, pos0, obs0, V, F, C, util::Normalization(-0.5, 0.5), vivid::ColorMap::Preset::CoolWarm, 1);
    // Lattice::plotSiteObs(triang, pos1, obs1, V, F, C, util::Normalization(-0.5, 0.5), vivid::ColorMap::Preset::CoolWarm, 0);
    // Lattice::plotBondObs(triang, start, end, corr, V, F, C, util::Normalization(min,max), vivid::ColorMap::Preset::Turbo, 1, 1);
    // Lattice::plotBondObs(triang, starte, ende, corre, V, F, C, util::Normalization(min,max), vivid::ColorMap::Preset::Turbo, 0, 0);
    // Lattice::plotBondObs(triang, startK, endK, corrK, V, F, C, util::Normalization(min,max), vivid::ColorMap::Preset::Turbo, 0, 1);
    // Lattice::drawVertices(triang, 1, V, F, C);
    // square.draw([](std::size_t a, std::size_t b, std::size_t distance) {return (a==1 and b==1) ? false:true;}, V,F,C);

    C60 mol;
    mol.initializeVertexMap(QuViz::MapType::Cuthill);
    std::cout << base_path + "/" + filename << std::endl;
    if(TWO_SITE) {
        auto [start, end, Scorr] = IO::loadBondObs(base_path + "/" + filename);
        Mol::plotBondObs(mol, start, end, Scorr, util::Normalization(Scorr.minCoeff(), Scorr.maxCoeff()), V, F, C, vivid::ColorMap::Preset::Magma);
    } else {
        auto [pos, obs] = IO::loadSiteObs(base_path + "/" + filename);
        Mol::plotSiteObs(mol, pos, obs, util::Normalization(obs.minCoeff(), obs.maxCoeff()), V, F, C, vivid::ColorMap::Preset::Vivid);
    }
    mol.colors_f.resize(mol.faces.size());
    for(std::size_t i = 0; i < mol.faces.size(); i++) { mol.colors_f[i] = (i < 6) ? vivid::Color("grey") : vivid::Color("grey"); }
    Mol::drawFaces(mol, V, F, C);
    std::cout << V.rows() << ", " << F.rows() << ", " << C.rows() << std::endl;

    // Plot the mesh
    igl::opengl::glfw::Viewer viewer;
    viewer.callback_key_down = &key_down;
    igl::opengl::glfw::imgui::ImGuiMenu menu;
    // menu.callback_draw_viewer_window = [](){};
    viewer.plugins.push_back(&menu);
    viewer.data().set_mesh(V, F);
    viewer.data().set_colors(C);
    viewer.data().show_lines = false;
    viewer.data().show_custom_labels = false;

    // for (std::size_t i=0; i<mol.vertices.size(); i++) {
    //         std::stringstream ss; ss << i;
    //         // std::cout << ss.str() << std::endl;
    //         Point pos; pos << mol.vertices[mol.schlegel_map_i.at(i)][0], mol.vertices[mol.schlegel_map_i.at(i)][1],
    //         mol.vertices[mol.schlegel_map_i.at(i)][2];
    //         // std::stringstream ss; ss << i;
    //         // Point pos; pos << mol.vertices[i][0], mol.vertices[i][1], mol.vertices[i][2];
    //         viewer.data().add_label(pos,ss.str());
    // }

    // viewer.core().is_animating = false;
    // viewer.core().animation_max_fps = 10;
    viewer.launch();
}
