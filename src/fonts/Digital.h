#ifndef DIGITAL_H_
#define DIGITAL_H_

#include "Eigen/Dense"

#include "fonts/FontOptions.h"

#include "GlobalTypedefs.h"
#include "shapes/Rectangle.h"
#include "shapes/Circle.h"

struct Digital
{
        Digital(const FontOptions& opt_in) : opt(opt_in) {}
        
        void draw(const char c, const Point& offset, Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const;

        //           1
        //     |    ___      |delta
        //     |   |   |
        //     |  6|   |2
        //     |   |___|
        //size |   | 7 |
        //     |  5|   |3
        //     |   |___|
        //     |     4
        //      0
        // 0: origin

        void draw1(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const;
        void draw2(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const;
        void draw3(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const;
        void draw4(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const;
        void draw5(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const;
        void draw6(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const;
        void draw7(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const;
        
        void draw_dot(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const;

        double glyph_width(const char c) const;
        
        FontOptions opt;
        double aspect_ratio=0.5;
        double space_ratio=0.15;
        double line_width_ratio = 0.08;
        double bold_line_width_ratio = 0.14;
        double width() const { return aspect_ratio*opt.size; } 
        double height() const { return opt.size; }
        double delta() const { return space_ratio*opt.size; }
        double line_width() const { return (opt.bold) ? bold_line_width_ratio*opt.size : line_width_ratio*opt.size;}
        
};

#endif
