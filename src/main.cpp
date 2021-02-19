#include <cstdint>
#include <algorithm>
#include <iostream>

#include <igl/embree/EmbreeRenderer.h>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/png/render_to_png.h>
#include <igl/png/writePNG.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuiHelpers.h>
#include <imgui/imgui.h>

#include "util/Export.h"
#include "IO/Io.h"

#include "vivid/vivid.h"

#include "Square.h"
#include "Rectangle.h"
#include "Polygon.h"
#include "Circle.h"
#include "Cuboid.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Tube.h"
#include "Sphere.h"
#include "molecules/C60.h"
#include "molecules/Drawing.h"

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
        double b = 0.05;

        C60 mol;
        auto [pos1,obs1] = IO::loadSiteObs("/home/user/__LIBS__/QuViz/src/examples/C60_triplet_S.dat");
        auto [start, end, Scorr] = IO::loadBondObs("/home/user/__LIBS__/QuViz/src/examples/C60_triplet_Scorr.dat");
        Mol::plotSiteObs(mol,pos1,obs1,V,F,C,vivid::ColorMap::Preset::Viridis);
        Mol::plotBondObs(mol,start,end,Scorr,V,F,C);
        Mol::drawFaces(mol,V,F,C);
        
        std::vector<Tube> ts;
        Eigen::Vector3d axis = (std::sqrt(1./9.)*Eigen::Vector3d::UnitY()+std::sqrt(3./9.)*Eigen::Vector3d::UnitY()+std::sqrt(5./9.)*Eigen::Vector3d::UnitZ());
        axis /= axis.norm();
        ts.push_back(Tube(5*b,Eigen::Vector3d::Zero(),5.*axis,vivid::Color("green")));
        
        ts.push_back(Tube(b,Eigen::Vector3d::Zero(),5.*Eigen::Vector3d::UnitX(),vivid::Color("purple")));
        ts.push_back(Tube(b,Eigen::Vector3d::Zero(),5.*Eigen::Vector3d::UnitY(),vivid::Color("red")));
        ts.push_back(Tube(b,Eigen::Vector3d::Zero(),5.*Eigen::Vector3d::UnitZ(),vivid::Color("blue")));

        // std::for_each(ts.begin(), ts.end(), [] (const Tube& t) {t.draw(V,F,C);});

        std::cout << V.rows() << ", " << F.rows() << ", " << C.rows() << std::endl;

        // Plot the mesh
        igl::embree::EmbreeRenderer er;
        er.set_mesh(V,F,true);
        er.set_colors(C);
        er.set_zoom(1.5);
        er.set_orthographic(false);
        Point translation; translation << 0.,0.,-0.5;
        er.set_translation(translation);
        // igl::opengl::glfw::Viewer viewer;
        // viewer.callback_key_down = &key_down;
        // igl::opengl::glfw::imgui::ImGuiMenu menu;
        // // menu.callback_draw_viewer_window = [](){};
        // viewer.plugins.push_back(&menu);
        // viewer.data().set_mesh(V, F);
        // viewer.data().set_colors(C);
        // viewer.data().show_lines = false;
        // viewer.core().is_animating = false;
        // // viewer.core().animation_max_fps = 10;

        // // GifAnim ganim;
        // // GifWriter g;
        // // ganim.GifBegin(&g, "C60.gif", 800, 1280, 20, 1, 8, false);

        // // viewer.callback_pre_draw = AnimHelper::createGif(0.1, Eigen::Vector3f::UnitY(), viewer, ganim, g);
        // FileFormats::PNGOptions pngOptions;
        // Export::PNG("C60.png", pngOptions, 0., 1./std::sqrt(2.)*(Eigen::Vector3d::UnitY()+Eigen::Vector3d::UnitX()), er);
        
        FileFormats::GifOptions gifOptions;
        gifOptions.framedelay=5;
        gifOptions.loopcount=2;
        Export::GIF("C60.gif", gifOptions, 100, axis, er);
        // viewer.launch();
        // ganim.GifEnd(&g);
}
