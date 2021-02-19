#include <cstdint>
#include <algorithm>
#include <iostream>

#include <igl/opengl/glfw/Viewer.h>
#include <igl/png/render_to_png.h>
#include <igl/png/writePNG.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuiHelpers.h>
#include <imgui/imgui.h>

#include "IO/Io.h"
int file_id = 0;
#include "vivid/vivid.h"

#include "lattices/Lattice2d.h"
#include "lattices/LatticeDefs.h"
#include "lattices/Drawing.h"

bool key_down(igl::opengl::glfw::Viewer& viewer, unsigned char key, int modifier)
{
  if (key == '1')
  {
    // Allocate temporary buffers
    Eigen::Matrix<unsigned char,Eigen::Dynamic,Eigen::Dynamic> R(1280,800);
    Eigen::Matrix<unsigned char,Eigen::Dynamic,Eigen::Dynamic> G(1280,800);
    Eigen::Matrix<unsigned char,Eigen::Dynamic,Eigen::Dynamic> B(1280,800);
    Eigen::Matrix<unsigned char,Eigen::Dynamic,Eigen::Dynamic> A(1280,800);

    // Draw the scene in the buffers
    viewer.core().draw_buffer(
                              viewer.data(),false,R,G,B,A);

    // Save it to a PNG
    std::stringstream ss;
    ss << "C60_" << file_id << ".png";
    file_id++;
    igl::png::writePNG(R,G,B,A,ss.str());
  }
  else if (key == '2') {
          Eigen::Matrix3f rot;
          rot = Eigen::AngleAxisf(0.01*M_PI,Eigen::Vector3f::UnitZ());
          viewer.core().camera_up = rot * viewer.core().camera_up;
          std::cout << viewer.core().camera_up.transpose() << std::endl;
  }
  else if (key == '3') {
          Eigen::Matrix3f rot;
          rot = Eigen::AngleAxisf(0.01*M_PI,Eigen::Vector3f::UnitZ());
          viewer.core().camera_up = rot.transpose() * viewer.core().camera_up;
          std::cout << viewer.core().camera_up.transpose() << std::endl;
  }
  else if (key == '4') {
          viewer.core().camera_zoom *= 1.01;
          std::cout << viewer.core().camera_zoom << std::endl;
  }
  else if (key == '5') {
          viewer.core().camera_zoom *= 0.99;
          std::cout << viewer.core().camera_zoom << std::endl;
  }
  else if (key == '6') {
          viewer.core().camera_view_angle *= 2.;
          std::cout << viewer.core().camera_view_angle << std::endl;
  }
  else if (key == '7') {
          viewer.core().camera_view_angle *= 0.5;
          std::cout << viewer.core().camera_view_angle << std::endl;
  }
  return false;
}

Eigen::Matrix<double,Eigen::Dynamic,3> V;
Eigen::Matrix<int,Eigen::Dynamic,3> F;
Eigen::Matrix<double,Eigen::Dynamic,3> C;

int main(int argc, char *argv[])
{
        // std::size_t nlabs = static_cast<std::size_t>(std::stoi(argv[1]));
        // std::cout << "nlabs=" << nlabs << std::endl;
        double b = 0.8;
        double c = 0.6;

        // std::array<Point,2> basis = {b*Eigen::Vector3d::UnitX(), b*Eigen::Vector3d::UnitY()};
        // std::vector<double> distances(1,c); distances.push_back(b);
        // std::vector<Point> unit_cell(2); unit_cell[0] = Eigen::Vector3d::Zero(); unit_cell[1] = -c*Eigen::Vector3d::UnitZ();
        auto [basis, distances, unit_cell] = Lattice::make_triang(b,1,Lattice::TRIANG_TYPE::YC);
        unit_cell.push_back(-c*Eigen::Vector3d::UnitZ());
        distances.push_back(b); distances[1]=c;
        // Lattice2d triang(8,8,basis,distances,unit_cell, [] (int ix, int iy) {return std::array<int,2>{ix-std::floor(static_cast<double>(iy)/2.), iy};});
        Lattice2d triang(8,8,basis,distances,unit_cell, [] (int ix, int iy) {return std::array<int,2>{ix, iy-std::floor(static_cast<double>(ix)/2.)};});
        triang.colors_v[0].push_back(vivid::Color("red"));
        triang.colors_v[1].push_back(vivid::Color("blue"));

        // if (type_ == LatticeType::TRIANG or type_ == LatticeType::SQUARE)
	// {
	// 	out = i[0]*a[0] + i[1]*a[1];
	// }
	// else if (type_ == LatticeType::TRIANG_XC)
	// {
	// 	out = (i[0]-std::floor(static_cast<double>(i[1])/2.))*a[0] + i[1]*a[1];
	// }
	// else if (type_ == LatticeType::TRIANG_YC)
	// {
	// 	out = i[0]*a[0] + (i[1]-std::floor(static_cast<double>(i[0])/2.))*a[1];
	// }
                
        
        Lattice::drawVertices(triang, 0, V, F, C);
        Lattice::drawVertices(triang, 1, V, F, C);
        // square.draw([](std::size_t a, std::size_t b, std::size_t distance) {return (a==1 and b==1) ? false:true;}, V,F,C);
        
        // std::vector<Tube> ts;
        // Eigen::Vector3d axis = (std::sqrt(1./9.)*Eigen::Vector3d::UnitY()+std::sqrt(3./9.)*Eigen::Vector3d::UnitY()+std::sqrt(5./9.)*Eigen::Vector3d::UnitZ());
        // axis /= axis.norm();
        // ts.push_back(Tube(5*b,Eigen::Vector3d::Zero(),5.*axis,vivid::Color("green")));
        
        // ts.push_back(Tube(b,Eigen::Vector3d::Zero(),5.*Eigen::Vector3d::UnitX(),vivid::Color("purple")));
        // ts.push_back(Tube(b,Eigen::Vector3d::Zero(),5.*Eigen::Vector3d::UnitY(),vivid::Color("red")));
        // ts.push_back(Tube(b,Eigen::Vector3d::Zero(),5.*Eigen::Vector3d::UnitZ(),vivid::Color("blue")));

        // std::for_each(ts.begin(), ts.end(), [] (const Tube& t) {t.draw(V,F,C);});

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
        // viewer.core().is_animating = false;
        // viewer.core().animation_max_fps = 10;
        viewer.launch();
}
