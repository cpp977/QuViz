#ifndef SOD20_H_
#define SOD20_H_

#include <array>
#include <map>

#include "vivid/color.h"

#include "IO/Io.h"

#include "shapes/Polygon.h"
#include "shapes/Sphere.h"
#include "shapes/Tube.h"

struct SOD20
{
    SOD20() {}
    SOD20(const std::vector<vivid::Color>& colors_v_in, const std::vector<vivid::Color>& colors_e_in, const std::vector<vivid::Color>& colors_f_in)
        : colors_v(colors_v_in)
        , colors_e(colors_e_in)
        , colors_f(colors_f_in)
    {}

    std::string name() const { return "SOD20"; }

    void initializeVertexMap(const QuViz::MapType& opt, const std::string& filename = "");

    std::vector<vivid::Color> colors_v, colors_e, colors_f;

    double vertex_diameter = 0.06;
    double edge_diameter = 0.02;

    std::map<std::size_t, std::size_t> vertex_map;

    static const std::map<std::size_t, std::size_t> spiral_map_i;
    static const std::map<std::size_t, std::size_t> spiral_map;
    static const std::array<std::vector<int>, 30> faces;
    std::vector<std::array<int, 2>> edges;

    static constexpr double C0 = 0.7071067811865475244008443621048; // = sqrt(2) / 2
    static constexpr double h = 0.2;

    static constexpr std::array<std::array<double, 3>, 20> vertices = {
        /*0 */ std::array<double, 3>{C0, 0.0, C0},
        /*1 */ std::array<double, 3>{C0, 0.0, -C0},
        /*2 */ std::array<double, 3>{-C0, 0.0, C0},
        /*3 */ std::array<double, 3>{-C0, 0.0, -C0},
        /*4 */ std::array<double, 3>{C0, C0, 0.0},
        /*5 */ std::array<double, 3>{C0, -C0, 0.0},
        /*6 */ std::array<double, 3>{-C0, C0, 0.0},
        /*7 */ std::array<double, 3>{-C0, -C0, 0.0},
        /*8 */ std::array<double, 3>{0.0, C0, C0},
        /*9 */ std::array<double, 3>{0.0, C0, -C0},
        /*10*/ std::array<double, 3>{0.0, -C0, C0},
        /*11*/ std::array<double, 3>{0.0, -C0, -C0},

        /*12*/ std::array<double, 3>{+(1. + h) * 2. / 3. * C0, +(1. + h) * 2. / 3. * C0, +(1. + h) * 2. / 3. * C0},
        /*13*/ std::array<double, 3>{+(1. + h) * 2. / 3. * C0, +(1. + h) * 2. / 3. * C0, -(1. + h) * 2. / 3. * C0},
        /*14*/ std::array<double, 3>{-(1. + h) * 2. / 3. * C0, +(1. + h) * 2. / 3. * C0, -(1. + h) * 2. / 3. * C0},
        /*15*/ std::array<double, 3>{-(1. + h) * 2. / 3. * C0, +(1. + h) * 2. / 3. * C0, +(1. + h) * 2. / 3. * C0},

        /*16*/ std::array<double, 3>{+(1. + h) * 2. / 3. * C0, -(1. + h) * 2. / 3. * C0, +(1. + h) * 2. / 3. * C0},
        /*17*/ std::array<double, 3>{+(1. + h) * 2. / 3. * C0, -(1. + h) * 2. / 3. * C0, -(1. + h) * 2. / 3. * C0},
        /*18*/ std::array<double, 3>{-(1. + h) * 2. / 3. * C0, -(1. + h) * 2. / 3. * C0, -(1. + h) * 2. / 3. * C0},
        /*19*/ std::array<double, 3>{-(1. + h) * 2. / 3. * C0, -(1. + h) * 2. / 3. * C0, +(1. + h) * 2. / 3. * C0}};
};

#endif
