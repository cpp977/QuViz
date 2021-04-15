#ifndef SOD60_H_
#define SOD60_H_

#include <array>
#include <map>

#include "vivid/color.h"

#include "IO/Io.h"

#include "shapes/Polygon.h"
#include "shapes/Sphere.h"
#include "shapes/Tube.h"

struct SOD60
{
    SOD60() {}
    SOD60(const std::vector<vivid::Color>& colors_v_in, const std::vector<vivid::Color>& colors_e_in, const std::vector<vivid::Color>& colors_f_in)
        : colors_v(colors_v_in)
        , colors_e(colors_e_in)
        , colors_f(colors_f_in)
    {}

    std::string name() const { return "SOD60"; }

    void initializeVertexMap(const QuViz::MapType& opt, const std::string& filename = "");

    std::vector<vivid::Color> colors_v, colors_e, colors_f;

    double vertex_diameter = 0.15;
    double edge_diameter = 0.05;

    std::map<std::size_t, std::size_t> vertex_map;

    static const std::map<std::size_t, std::size_t> spiral_map_i;
    static const std::map<std::size_t, std::size_t> spiral_map;
    static const std::array<std::vector<int>, 86> faces;
    std::vector<std::array<int, 2>> edges;

    static constexpr double C0 = 0.7071067811865475244008443621048; // = sqrt(2) / 2
    static constexpr double h = 0.4;

    static constexpr std::array<std::array<double, 3>, 60> vertices = {
        /* 0*/ std::array<double, 3>{0.5, 0.5, 2.0},
        /* 1*/ std::array<double, 3>{0.5, 0.5, -2.0},
        /* 2*/ std::array<double, 3>{0.5, -0.5, 2.0},
        /* 3*/ std::array<double, 3>{0.5, -0.5, -2.0},
        /* 4*/ std::array<double, 3>{-0.5, 0.5, 2.0},
        /* 5*/ std::array<double, 3>{-0.5, 0.5, -2.0},
        /* 6*/ std::array<double, 3>{-0.5, -0.5, 2.0},
        /* 7*/ std::array<double, 3>{-0.5, -0.5, -2.0},
        /* 8*/ std::array<double, 3>{2.0, 0.5, 0.5},
        /* 9*/ std::array<double, 3>{2.0, 0.5, -0.5},
        /*10*/ std::array<double, 3>{2.0, -0.5, 0.5},
        /*11*/ std::array<double, 3>{2.0, -0.5, -0.5},
        /*12*/ std::array<double, 3>{-2.0, 0.5, 0.5},
        /*13*/ std::array<double, 3>{-2.0, 0.5, -0.5},
        /*14*/ std::array<double, 3>{-2.0, -0.5, 0.5},
        /*15*/ std::array<double, 3>{-2.0, -0.5, -0.5},
        /*16*/ std::array<double, 3>{0.5, 2.0, 0.5},
        /*17*/ std::array<double, 3>{0.5, 2.0, -0.5},
        /*18*/ std::array<double, 3>{0.5, -2.0, 0.5},
        /*19*/ std::array<double, 3>{0.5, -2.0, -0.5},
        /*20*/ std::array<double, 3>{-0.5, 2.0, 0.5},
        /*21*/ std::array<double, 3>{-0.5, 2.0, -0.5},
        /*22*/ std::array<double, 3>{-0.5, -2.0, 0.5},
        /*23*/ std::array<double, 3>{-0.5, -2.0, -0.5},
        /*24*/ std::array<double, 3>{1.5, 0.0, 1.5},
        /*25*/ std::array<double, 3>{1.5, 0.0, -1.5},
        /*26*/ std::array<double, 3>{-1.5, 0.0, 1.5},
        /*27*/ std::array<double, 3>{-1.5, 0.0, -1.5},
        /*28*/ std::array<double, 3>{1.5, 1.5, 0.0},
        /*29*/ std::array<double, 3>{1.5, -1.5, 0.0},
        /*30*/ std::array<double, 3>{-1.5, 1.5, 0.0},
        /*31*/ std::array<double, 3>{-1.5, -1.5, 0.0},
        /*32*/ std::array<double, 3>{0.0, 1.5, 1.5},
        /*33*/ std::array<double, 3>{0.0, 1.5, -1.5},
        /*34*/ std::array<double, 3>{0.0, -1.5, 1.5},
        /*35*/ std::array<double, 3>{0.0, -1.5, -1.5},

        /*36*/ std::array<double, 3>{+(1. + h) * 1. / 3. * 2.5, 0.0, +(1. + h) * 1. / 3. * 5.5},
        /*36*/ std::array<double, 3>{0.0, +(1. + h) * 1. / 3. * 2.5, +(1. + h) * 1. / 3. * 5.5},
        /*37*/ std::array<double, 3>{0.0, -(1. + h) * 1. / 3. * 2.5, +(1. + h) * 1. / 3. * 5.5},
        /*38*/ std::array<double, 3>{-(1. + h) * 1. / 3. * 2.5, 0.0, +(1. + h) * 1. / 3. * 5.5},

        /*40*/ std::array<double, 3>{0.0, +(1. + h) * 1. / 3. * 2.5, -(1. + h) * 1. / 3. * 5.5},
        /*41*/ std::array<double, 3>{+(1. + h) * 1. / 3. * 2.5, 0.0, -(1. + h) * 1. / 3. * 5.5},
        /*42*/ std::array<double, 3>{0.0, -(1. + h) * 1. / 3. * 2.5, -(1. + h) * 1. / 3. * 5.5},
        /*43*/ std::array<double, 3>{-(1. + h) * 1. / 3. * 2.5, 0.0, -(1. + h) * 1. / 3. * 5.5},

        /*44*/ std::array<double, 3>{+(1. + h) * 1. / 3. * 5.5, +(1. + h) * 1. / 3. * 2.5, 0.0},
        /*45*/ std::array<double, 3>{+(1. + h) * 1. / 3. * 5.5, 0.0, +(1. + h) * 1. / 3. * 2.5},
        /*46*/ std::array<double, 3>{+(1. + h) * 1. / 3. * 5.5, 0.0, -(1. + h) * 1. / 3. * 2.5},
        /*47*/ std::array<double, 3>{+(1. + h) * 1. / 3. * 5.5, -(1. + h) * 1. / 3. * 2.5, 0.0},

        /*48*/ std::array<double, 3>{-(1. + h) * 1. / 3. * 5.5, 0.0, +(1. + h) * 1. / 3. * 2.5},
        /*49*/ std::array<double, 3>{-(1. + h) * 1. / 3. * 5.5, +(1. + h) * 1. / 3. * 2.5, 0.0},
        /*50*/ std::array<double, 3>{-(1. + h) * 1. / 3. * 5.5, 0.0, -(1. + h) * 1. / 3. * 2.5},
        /*51*/ std::array<double, 3>{-(1. + h) * 1. / 3. * 5.5, -(1. + h) * 1. / 3. * 2.5, 0.0},

        /*52*/ std::array<double, 3>{0.0, +(1. + h) * 1. / 3. * 5.5, +(1. + h) * 1. / 3. * 2.5},
        /*53*/ std::array<double, 3>{+(1. + h) * 1. / 3. * 2.5, +(1. + h) * 1. / 3. * 5.5, 0.0},
        /*54*/ std::array<double, 3>{0.0, +(1. + h) * 1. / 3. * 5.5, -(1. + h) * 1. / 3. * 2.5},
        /*55*/ std::array<double, 3>{+(1. + h) * 1. / 3. * 2.5, -(1. + h) * 1. / 3. * 5.5, 0.0},

        /*56*/ std::array<double, 3>{0.0, -(1. + h) * 1. / 3. * 5.5, +(1. + h) * 1. / 3. * 2.5},
        /*57*/ std::array<double, 3>{0.0, -(1. + h) * 1. / 3. * 5.5, -(1. + h) * 1. / 3. * 2.5},
        /*58*/ std::array<double, 3>{-(1. + h) * 1. / 3. * 2.5, +(1. + h) * 1. / 3. * 5.5, 0.0},
        /*59*/ std::array<double, 3>{-(1. + h) * 1. / 3. * 2.5, -(1. + h) * 1. / 3. * 5.5, 0.0}

        // /*12*/ std::array<double,3>{+(1.+h)*2./3.*C0, +(1.+h)*2./3.*C0, +(1.+h)*2./3.*C0},
        // /*13*/ std::array<double,3>{+(1.+h)*2./3.*C0, +(1.+h)*2./3.*C0, -(1.+h)*2./3.*C0},
        // /*14*/ std::array<double,3>{-(1.+h)*2./3.*C0, +(1.+h)*2./3.*C0, -(1.+h)*2./3.*C0},
        // /*15*/ std::array<double,3>{-(1.+h)*2./3.*C0, +(1.+h)*2./3.*C0, +(1.+h)*2./3.*C0},

        // /*16*/ std::array<double,3>{+(1.+h)*2./3.*C0, -(1.+h)*2./3.*C0, +(1.+h)*2./3.*C0},
        // /*17*/ std::array<double,3>{+(1.+h)*2./3.*C0, -(1.+h)*2./3.*C0, -(1.+h)*2./3.*C0},
        // /*18*/ std::array<double,3>{-(1.+h)*2./3.*C0, -(1.+h)*2./3.*C0, -(1.+h)*2./3.*C0},
        // /*19*/ std::array<double,3>{-(1.+h)*2./3.*C0, -(1.+h)*2./3.*C0, +(1.+h)*2./3.*C0}
    };
};

#endif
