#ifndef C60_H_
#define C60_H_

#include <array>
#include <map>

#include "vivid/color.h"

#include "shapes/Polygon.h"
#include "shapes/Tube.h"
#include "shapes/Sphere.h"

struct C60
{
        C60() {}
        C60(const std::vector<vivid::Color>& colors_v_in, const std::vector<vivid::Color>& colors_e_in, const std::vector<vivid::Color>& colors_f_in)
                : colors_v(colors_v_in),colors_e(colors_e_in),colors_f(colors_f_in) {}
        
        std::vector<vivid::Color> colors_v, colors_e, colors_f;

        double vertex_diameter = 0.2;
        double edge_diameter = 0.1;
        
        static constexpr double C0 = 0.809016994374947424102293417183;// = (1 + sqrt(5)) / 4;
        static constexpr double C1 = 1.61803398874989484820458683437;//  = (1 + sqrt(5)) / 2;
        static constexpr double C2 = 1.80901699437494742410229341718;//  = (5 + sqrt(5)) / 4;
        static constexpr double C3 = 2.11803398874989484820458683437;//  = (2 + sqrt(5)) / 2;
        static constexpr double C4 = 2.427050983124842272306880251548;// = 3 * (1 + sqrt(5)) / 4;

        static const std::map<std::size_t, std::size_t> schlegel_map_i;
        static const std::map<std::size_t, std::size_t> schlegel_map;
        static const std::array<std::vector<int>,32> faces;
        std::array<std::array<int,2>,90> edges;


        static constexpr std::array<std::array<double,3>,60> vertices = {
                std::array<double,3>{ 0.5,  0.0,   C4},
                std::array<double,3>{ 0.5,  0.0,  -C4},
                std::array<double,3>{-0.5,  0.0,   C4},
                std::array<double,3>{-0.5,  0.0,  -C4},
                std::array<double,3>{  C4,  0.5,  0.0},
                std::array<double,3>{  C4, -0.5,  0.0},
                std::array<double,3>{ -C4,  0.5,  0.0},
                std::array<double,3>{ -C4, -0.5,  0.0},
                std::array<double,3>{ 0.0,   C4,  0.5},
                std::array<double,3>{ 0.0,   C4, -0.5},
                std::array<double,3>{ 0.0,  -C4,  0.5},
                std::array<double,3>{ 0.0,  -C4, -0.5},
                std::array<double,3>{ 1.0,   C0,   C3},
                std::array<double,3>{ 1.0,   C0,  -C3},
                std::array<double,3>{ 1.0,  -C0,   C3},
                std::array<double,3>{ 1.0,  -C0,  -C3},
                std::array<double,3>{-1.0,   C0,   C3},
                std::array<double,3>{-1.0,   C0,  -C3},
                std::array<double,3>{-1.0,  -C0,   C3},
                std::array<double,3>{-1.0,  -C0,  -C3},
                std::array<double,3>{  C3,  1.0,   C0},
                std::array<double,3>{  C3,  1.0,  -C0},
                std::array<double,3>{  C3, -1.0,   C0},
                std::array<double,3>{  C3, -1.0,  -C0},
                std::array<double,3>{ -C3,  1.0,   C0},
                std::array<double,3>{ -C3,  1.0,  -C0},
                std::array<double,3>{ -C3, -1.0,   C0},
                std::array<double,3>{ -C3, -1.0,  -C0},
                std::array<double,3>{  C0,   C3,  1.0},
                std::array<double,3>{  C0,   C3, -1.0},
                std::array<double,3>{  C0,  -C3,  1.0},
                std::array<double,3>{  C0,  -C3, -1.0},
                std::array<double,3>{ -C0,   C3,  1.0},
                std::array<double,3>{ -C0,   C3, -1.0},
                std::array<double,3>{ -C0,  -C3,  1.0},
                std::array<double,3>{ -C0,  -C3, -1.0},
                std::array<double,3>{ 0.5,   C1,   C2},
                std::array<double,3>{ 0.5,   C1,  -C2},
                std::array<double,3>{ 0.5,  -C1,   C2},
                std::array<double,3>{ 0.5,  -C1,  -C2},
                std::array<double,3>{-0.5,   C1,   C2},
                std::array<double,3>{-0.5,   C1,  -C2},
                std::array<double,3>{-0.5,  -C1,   C2},
                std::array<double,3>{-0.5,  -C1,  -C2},
                std::array<double,3>{  C2,  0.5,   C1},
                std::array<double,3>{  C2,  0.5,  -C1},
                std::array<double,3>{  C2, -0.5,   C1},
                std::array<double,3>{  C2, -0.5,  -C1},
                std::array<double,3>{ -C2,  0.5,   C1},
                std::array<double,3>{ -C2,  0.5,  -C1},
                std::array<double,3>{ -C2, -0.5,   C1},
                std::array<double,3>{ -C2, -0.5,  -C1},
                std::array<double,3>{  C1,   C2,  0.5},
                std::array<double,3>{  C1,   C2, -0.5},
                std::array<double,3>{  C1,  -C2,  0.5},
                std::array<double,3>{  C1,  -C2, -0.5},
                std::array<double,3>{ -C1,   C2,  0.5},
                std::array<double,3>{ -C1,   C2, -0.5},
                std::array<double,3>{ -C1,  -C2,  0.5},
                std::array<double,3>{ -C1,  -C2, -0.5},
        };        
};
#endif
