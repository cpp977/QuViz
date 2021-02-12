#include <algorithm>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/png/render_to_png.h>
#include <igl/png/writePNG.h>
#include <igl/xml/writeDAE.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>

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

int file_id=0;
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

  return false;
}

Eigen::Matrix<double,Eigen::Dynamic,3> V;
Eigen::Matrix<int,Eigen::Dynamic,3> F;
Eigen::Matrix<double,Eigen::Dynamic,3> C;

int main(int argc, char *argv[])
{
        double a=0.2;
        double b=0.05;
        double c=1.;
        // std::size_t nlabs = static_cast<std::size_t>(std::stoi(argv[1]));
        // std::cout << "nlabs=" << nlabs << std::endl;
        
        auto unitX = Eigen::Vector3d::UnitX();
        auto unitY = Eigen::Vector3d::UnitY();
        auto unitZ = Eigen::Vector3d::UnitZ();

        Eigen::VectorXd Scorr(90);
        Eigen::VectorXd start(90);
        Eigen::VectorXd end(90);
        start <<
                0, 
                1 ,
                2 ,
                0 ,
                3 ,
                4 ,
                5 ,
                6 ,
                0 ,
                7 ,
                8 ,
                9 ,
                1 ,
                10,
                11,
                12,
                2 ,
                13,
                14,
                15,
                3 ,
                16,
                17,
                5 ,
                18,
                19,
                6 ,
                20,
                21,
                22,
                7 ,
                23,
                9 ,
                24,
                25,
                26,
                10,
                27,
                12,
                28,
                29,
                30,
                13,
                31,
                15,
                32,
                33,
                34,
                16,
                35,
                18,
                36,
                37,
                20,
                38,
                39,
                22,
                40,
                41,
                23,
                42,
                26,
                43,
                44,
                27,
                45,
                30,
                46,
                47,
                31,
                48,
                34,
                49,
                50,
                35,
                51,
                38,
                52,
                40,
                53,
                54,
                42,
                55,
                45,
                56,
                48,
                57,
                51,
                55,
                58;
        end <<                
                1,  
                2,
                3,
                4,
                4,
                5,
                6,
                7,
                8,
                8,
                9,
                10,
                11,
                11,
                12,
                13,
                14,
                14,
                15,
                16,
                17,
                17,
                18,
                19,
                19,
                20,
                21,
                21,
                22,
                23,
                24,
                24,
                25,
                25,
                26,
                27,
                28,
                28,
                29,
                29,
                30,
                31,
                32,
                32,
                33,
                33,
                34,
                35,
                36,
                36,
                37,
                37,
                38,
                39,
                39,
                40,
                41,
                41,
                42,
                43,
                43,
                44,
                44,
                45,
                46,
                46,
                47,
                47,
                48,
                49,
                49,
                50,
                50,
                51,
                52,
                52,
                53,
                53,
                54,
                54,
                55,
                56,
                56,
                57,
                57,
                58,
                58,
                59,
                59,
                59;
        Scorr <<
                -0.281934383370747  ,
                -0.2799034514694852 ,
                -0.2862233877980604 ,
                -0.2846625431000406 ,
                -0.2785435413386934, 
                -0.4735508364556983 ,
                -0.2743961170387564 ,
                -0.4678173373845191 ,
                -0.4712179085451025 ,
                -0.2784753488988688 ,
                -0.2813104434225019 ,
                -0.4632339321136553 ,
                -0.4746515196797902 ,
                -0.2758707420419905 ,
                -0.2778739515732065 ,
                -0.4592078778168859 ,
                -0.4715092662583905 ,
                -0.2828840162619506 ,
                -0.2761069066137817 ,
                -0.4703423762001195 ,
                -0.4723328243263814 ,
                -0.2744845391905794 ,
                -0.2828787867446337 ,
                -0.280830688110757  ,
                -0.4559710654251943 ,
                -0.2846619266903094 ,
                -0.27972117174981   ,
                -0.3283776269125207 ,
                -0.414548193398845  ,
                -0.3287677250363693 ,
                -0.2765759203973299 ,
                -0.4196490804313904 ,
                -0.27819015744516   ,
                -0.3283250430895457 ,
                -0.4175504147815514 ,
                -0.3286371288793302 ,
                -0.2822542803423624 ,
                -0.4108438956286375 ,
                -0.2840221988132036 ,
                -0.3284282633329326 ,
                -0.4085670483547127 ,
                -0.3285918849562521 ,
                -0.2798363154838887 ,
                -0.4143653040109929 ,
                -0.2758504333155729 ,
                -0.3287234045112459 ,
                -0.4191511379779773 ,
                -0.3286406744016005 ,
                -0.276718530626013  ,
                -0.4171341592293338 ,
                -0.2820258587845191 ,
                -0.3289294286351686 ,
                -0.4104765975496675 ,
                -0.407673020278318  ,
                -0.3285031872138029 ,
                -0.2844137512111002 ,
                -0.2792617470190282 ,
                -0.4589897771894939 ,
                -0.2831649103656113 ,
                -0.2753200224215414 ,
                -0.2761915967790058 ,
                -0.2766690789031896 ,
                -0.4704900335356742 ,
                -0.2745389693914195 ,
                -0.2822042298000579 ,
                -0.2829015885419492 ,
                -0.2839282577194217 ,
                -0.4559780001818586 ,
                -0.2809794129985274 ,
                -0.2790839371173374 ,
                -0.2743799101802014 ,
                -0.2763137149512864 ,
                -0.4678233388454373 ,
                -0.2783819211711732 ,
                -0.2779844341301568 ,
                -0.2813443888634453 ,
                -0.2825288952259407 ,
                -0.4630063955307515 ,
                -0.2778308492487257 ,
                -0.2756763871454712 ,
                -0.4746952811295869 ,
                -0.471285916560563  ,
                -0.2798748041873465 ,
                -0.4722573910479758 ,
                -0.2863701013114229 ,
                -0.4735283928479275 ,
                -0.2784916913161536 ,
                -0.471242599635169  ,
                -0.2818630310840239 ,
                -0.2846799509868186 ;
        
        Eigen::VectorXd vals(60);
        vals << 
        	0.008075705931037815,
                0.009117338238675634,
                0.008008869839212509,
                0.009376476741256419,
                0.00884631243997957,
                -0.0002267104759345186,
                0.01286036804949992,
                0.01444479804649697,
                -0.0002158429161910936,
                0.01638661135742717,
                0.01539110109235535,
                -0.0002044345267613537,
                0.01583821723120046,
                0.01745492238694521,
                0.0001458305597678469,
                0.01468284234089067,
                0.014471828126315,
                -0.0003557431216018651,
                0.01905946462494635,
                0.01751144974488143,
                0.03278793412035263,
                0.02793827406640569,
                0.02951437319265407,
                0.02671123280256494,
                0.02643577385378957,
                0.02843060974642779,
                0.02787476717723554,
                0.03180292554247328,
                0.03028634378519009,
                0.03156455200905355,
                0.03153315314401094,
                0.02907504653464894,
                0.02917895180586269,
                0.02771950633820236,
                0.02738529393639565,
                0.029414443529278,
                0.02865783594950533,
                0.0315373513737565,
                0.0318248231578358,
                0.0310122647464353,
                0.01637516010736161,
                0.0180029328721288,
                -0.0009288611904790183,
                0.01499753585090208,
                0.01377128326875347,
                -0.0005289445929742975,
                0.01836587341146384,
                0.01864553502015233,
                -0.0008644365203215599,
                0.01433810512292796,
                0.01561132695898821,
                -0.0010227472511302,
                0.0180286306627344,
                0.01606338815059944,
                -0.000795145100378473,
                0.01015984530352162,
                0.00930195472650122,
                0.00967636447303076,
                0.01009530389517008,
                0.009352032308578898;

        // std::vector<RGB> colv(60);
        // std::vector<RGB> colf(32);
        // std::vector<RGB> cole(90);
        // Palette::cmap map(vals.minCoeff(),vals.maxCoeff());
        // Palette::cmap map_corr(-Scorr.maxCoeff(),-Scorr.minCoeff());
        // for (std::size_t i=0; i<60; i++) {
        //         colv[i] = map(vals(i));
        // }
        // for (std::size_t i=0; i<90; i++) {
        //         cole[i] = map_corr(std::abs(Scorr(i)));
        // }
        // for (std::size_t i=0; i<32; i++) {
        //         colf[i] = Palette::grey;
        //         // colf[i] = (i<20) ? Palette::green : Palette::purple;
        // }
        C60 mol;//(colv,cole,colf);
        // for (std::size_t i=0; i<90; i++) {
        //         mol.edges[i][0] = start(i);
        //         mol.edges[i][1] = end(i);
        // }
        Mol::plotOneSiteObs(mol,vals,V,F,C);
        Mol::plotTwoSiteObs(mol,start,end,Scorr,V,F,C);
        Mol::drawFaces(mol,V,F,C);
        
        
        // std::size_t Lx=12;
        // std::size_t Ly=6;
        // std::vector<Sphere> sps;
        // for (const auto& pos : C60) {
        //         sps.push_back(Sphere(a,pos,Palette::blue));
        // }
        // std::vector<Tube> ts;
        // for (std::size_t i=0; i<60; i++) {
        //         for (const auto& neigh:C60_n[i]) {
        //                 ts.push_back(Tube(b,C60[i],neigh,Palette::grey));
        //         }
        // }

        // ts.push_back(Tube(b,Eigen::Vector3d::Zero(),5.*Eigen::Vector3d::UnitX(),Palette::green));
        // ts.push_back(Tube(b,Eigen::Vector3d::Zero(),5.*Eigen::Vector3d::UnitY(),Palette::blue));
        // ts.push_back(Tube(b,Eigen::Vector3d::Zero(),5.*Eigen::Vector3d::UnitZ(),Palette::red));
        
        // std::vector<Cube> cs;
        // for (std::size_t ix=0; ix<Lx; ix++) {
        //         for (std::size_t iy=0; iy<Ly; iy++) {
        //                 // sps.push_back(Sphere(a,ix*unitX+iy*unitY,Palette::blue));
        //                 // sps.push_back(Sphere(a,ix*unitX+iy*unitY+c*unitZ,Palette::orange));
        //                 cs.push_back(Cube(a,ix*unitX+iy*unitY,Palette::blue));
        //                 cs.push_back(Cube(a,ix*unitX+iy*unitY+c*unitZ,Palette::orange));
        //         }
        // }
        // std::vector<Tube> ts;
        // for (std::size_t ix=0; ix<Lx; ix++) {
        //         for (std::size_t iy=0; iy<Ly; iy++) {
        //                 if (ix<Lx-1) ts.push_back(Tube(b,ix*unitX+iy*unitY,(ix+1)*unitX+iy*unitY,Palette::black));
        //                 if (iy<Ly-1) ts.push_back(Tube(b,ix*unitX+iy*unitY,ix*unitX+(iy+1)*unitY,Palette::black));
        //                 if (ix>0 and iy<Ly-1) ts.push_back(Tube(b,ix*unitX+iy*unitY,(ix-1)*unitX+(iy+1)*unitY,Palette::black));
        //                 // if (ix<Lx-1) ts.push_back(Tube(b,ix*unitX+iy*unitY+c*unitZ,(ix+1)*unitX+iy*unitY+c*unitZ,Palette::black));
        //                 // if (iy<Ly-1) ts.push_back(Tube(b,ix*unitX+iy*unitY+c*unitZ,ix*unitX+(iy+1)*unitY+c*unitZ,Palette::black));
        //                 // if (ix>0 and iy<Ly-1) ts.push_back(Tube(b,ix*unitX+iy*unitY+c*unitZ,(ix-1)*unitX+(iy+1)*unitY+c*unitZ,Palette::black));
        //                 ts.push_back(Tube(b,ix*unitX+iy*unitY,ix*unitX+(iy)*unitY+c*unitZ,Palette::black));
        //         }
        // }
        // std::for_each(sps.begin(), sps.end(), [] (const Sphere& s) {s.draw(V,F,C);});
        // std::for_each(cs.begin(), cs.end(), [] (const Cube& c) {c.draw(V,F,C);});
        // std::for_each(ts.begin(), ts.end(), [] (const Tube& t) {t.draw(V,F,C);});

        std::cout << V.rows() << ", " << F.rows() << ", " << C.rows() << std::endl;

        // igl::xml::writeDAE("C60.dae",V,F);
        
        // Plot the mesh
        igl::opengl::glfw::Viewer viewer;
        viewer.callback_key_down = &key_down;
        viewer.data().set_mesh(V, F);
        viewer.data().set_colors(C);
        // Eigen::Vector4f bc; bc << 0.,0.,0.,0.;
        // viewer.core().background_color = bc;
        // viewer.data().set_face_based(true);
        viewer.data().show_lines = false;

        // for (std::size_t i=0; i<60; i++) {
        //         Point p(mol.vertices[mol.schlegel_map.at(i)].data());
        //         std::stringstream ss;
        //         ss << i;
        //         viewer.data().add_label(p,ss.str());
        // }
        // viewer.data().show_custom_labels = true;


        // // Start imgui to render text annotations
        // igl::opengl::glfw::imgui::ImGuiMenu menu;
        // menu.callback_draw_viewer_window = [](){};
        // viewer.plugins.push_back(&menu);

        viewer.launch();
}
