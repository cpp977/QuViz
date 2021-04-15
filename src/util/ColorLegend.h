#ifndef COLOR_LEGEND_H_
#define COLOR_LEGEND_H_

#include "vivid/colormap.h"
#include "shapes/Rectangle.h"
#include "util/Normalization.h"

#include "render/TextRenderer.h"
#include "fonts/Digital.h"
#include "fonts/FontOptions.h"

namespace util {        
    void color_legend(const Point& offset, const vivid::ColorMap::Preset map, const double min, const double max, const double mid,
                      Eigen::Matrix<double, Eigen::Dynamic,3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C, double width=0.2) {
        vivid::ColorMap m(map);
        std::size_t N = m.numStops();

        double total_height=20*width;
        Normalization norm(min,max,mid);
        double height = total_height/N;
        
        std::vector<Rectangle> rs;
        for (std::size_t i=0; i<N; i++) {        
            rs.push_back(Rectangle(width,height,m.at(static_cast<double>(i)/N),0.,offset+i*height*Eigen::Vector3d::UnitY()));
        }
        std::for_each(rs.begin(), rs.end(), [&V,&F,&C] (const Rectangle& r) {r.draw(V,F,C);});

        FontOptions normal; normal.size = width;
        Digital d(normal);
        for (std::size_t i=0; i<N; i+=N/5) {
            double val = norm.invers(static_cast<double>(i)/N);
            TextRenderer<Digital> t(d, offset + 0.1*Eigen::Vector3d::UnitX() + i*height*Eigen::Vector3d::UnitY());
            t << val;
            t.render(V,F,C);
        }
    }

    void color_legend(const Point& offset, const vivid::ColorMap::Preset map, const double min, const double max,
                      Eigen::Matrix<double, Eigen::Dynamic,3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C, double width=0.2) {
        return color_legend(offset, map, min, max, 0.5*(max-min), V, F, C);
    }
}

#endif
