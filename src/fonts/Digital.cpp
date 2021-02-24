#include "Digital.h"

//           1
//     |    ___      |delta
//     |   |   |
//     |  6|   |2
//     |   |___|
//size |   | 7 |
//     |  5|   |3
//     |   |___|
//     |O    4
//      
// O: origin

void Digital::
draw1(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const
{
        Rectangle r(width()-delta(), line_width(), opt.color, 0., 0.5*width()*Eigen::Vector3d::UnitX() + (height()-delta())*Eigen::Vector3d::UnitY());
        r.draw(V,F,C);
}

void Digital::
draw2(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const
{
        Rectangle r(line_width(), 0.5*height()-delta(), opt.color, 0., (width()-0.5*delta())*Eigen::Vector3d::UnitX() + (0.75*height()-0.5*delta())*Eigen::Vector3d::UnitY());
        r.draw(V,F,C);
}

void Digital::
draw3(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const
{
        Rectangle r(line_width(), 0.5*height()-delta(), opt.color, 0., (width()-0.5*delta())*Eigen::Vector3d::UnitX() + (delta()+0.25*height()-0.5*delta())*Eigen::Vector3d::UnitY());
        r.draw(V,F,C);
}

void Digital::
draw4(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const
{
        Rectangle r(width()-delta(), line_width(), opt.color, 0., (0.5*width())*Eigen::Vector3d::UnitX() + (delta())*Eigen::Vector3d::UnitY());
        r.draw(V,F,C);
}

void Digital::
draw5(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const
{
        Rectangle r(line_width(), 0.5*height()-delta(), opt.color, 0., (0.5*delta())*Eigen::Vector3d::UnitX() + (delta()+0.25*height()-0.5*delta())*Eigen::Vector3d::UnitY());
        r.draw(V,F,C);
}

void Digital::
draw6(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const
{
        Rectangle r(line_width(), 0.5*height()-delta(), opt.color, 0., (0.5*delta())*Eigen::Vector3d::UnitX() + (0.75*height()-0.5*delta())*Eigen::Vector3d::UnitY());
        r.draw(V,F,C);
}

void Digital::
draw7(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const
{
        Rectangle r(width()-delta(), line_width(), opt.color, 0., (0.5*width())*Eigen::Vector3d::UnitX() + (0.5*height())*Eigen::Vector3d::UnitY());
        r.draw(V,F,C);
}

void Digital::
draw_dot(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const
{
        Circle r(line_width(), opt.color, 0.5*delta()*Eigen::Vector3d::UnitX() + (delta())*Eigen::Vector3d::UnitY());
        r.draw(V,F,C);
}

double Digital::
glyph_width(const char c) const
{
        if (c == '0' or c == '1' or c == '2' or c == '3' or c == '4' or c == '5' or c == '6' or c == '7' or c == '8' or c == '9' or c == '-') {
                return width();
        }
        else if (c == '.') {
                return 0.5*width();
        }                
}

void Digital::
draw(const char c, const Point& offset, Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const
{
        if (c == '0') {
                auto curr_size_V = V.rows();
                draw1(V,F,C);
                draw2(V,F,C);
                draw3(V,F,C);
                draw4(V,F,C);
                draw5(V,F,C);
                draw6(V,F,C);
                for (Eigen::Index r=curr_size_V; r<V.rows(); r++) {
                        V.row(r) += offset.transpose();
                }                
        }
        else if (c == '1') {
                auto curr_size_V = V.rows();
                draw2(V,F,C);
                draw3(V,F,C);
                for (Eigen::Index r=curr_size_V; r<V.rows(); r++) {
                        V.row(r) += offset.transpose();
                }                
        }
        else if (c == '2') {
                auto curr_size_V = V.rows();
                draw1(V,F,C);
                draw2(V,F,C);
                draw7(V,F,C);
                draw5(V,F,C);
                draw4(V,F,C);
                for (Eigen::Index r=curr_size_V; r<V.rows(); r++) {
                        V.row(r) += offset.transpose();
                }                
        }
        else if (c == '3') {
                auto curr_size_V = V.rows();
                draw1(V,F,C);
                draw2(V,F,C);
                draw3(V,F,C);
                draw4(V,F,C);
                draw7(V,F,C);
                for (Eigen::Index r=curr_size_V; r<V.rows(); r++) {
                        V.row(r) += offset.transpose();
                }                
        }
        else if (c == '4') {
                auto curr_size_V = V.rows();
                draw6(V,F,C);
                draw7(V,F,C);
                draw2(V,F,C);
                draw3(V,F,C);
                for (Eigen::Index r=curr_size_V; r<V.rows(); r++) {
                        V.row(r) += offset.transpose();
                }                
        }
        else if (c == '5') {
                auto curr_size_V = V.rows();
                draw1(V,F,C);
                draw6(V,F,C);
                draw7(V,F,C);
                draw3(V,F,C);
                draw4(V,F,C);
                for (Eigen::Index r=curr_size_V; r<V.rows(); r++) {
                        V.row(r) += offset.transpose();
                }                
        }
        else if (c == '6') {
                auto curr_size_V = V.rows();
                draw1(V,F,C);
                draw6(V,F,C);
                draw5(V,F,C);
                draw4(V,F,C);
                draw3(V,F,C);
                draw7(V,F,C);
                for (Eigen::Index r=curr_size_V; r<V.rows(); r++) {
                        V.row(r) += offset.transpose();
                }                
        }
        else if (c == '7') {
                auto curr_size_V = V.rows();
                draw1(V,F,C);
                draw2(V,F,C);
                draw3(V,F,C);
                for (Eigen::Index r=curr_size_V; r<V.rows(); r++) {
                        V.row(r) += offset.transpose();
                }                
        }
        else if (c == '8') {
                auto curr_size_V = V.rows();
                draw1(V,F,C);
                draw2(V,F,C);
                draw3(V,F,C);
                draw4(V,F,C);
                draw5(V,F,C);
                draw6(V,F,C);
                draw7(V,F,C);
                for (Eigen::Index r=curr_size_V; r<V.rows(); r++) {
                        V.row(r) += offset.transpose();
                }                
        }
        else if (c == '9') {
                auto curr_size_V = V.rows();
                draw1(V,F,C);
                draw2(V,F,C);
                draw3(V,F,C);
                draw4(V,F,C);
                draw6(V,F,C);
                draw7(V,F,C);
                for (Eigen::Index r=curr_size_V; r<V.rows(); r++) {
                        V.row(r) += offset.transpose();
                }                
        }
        else if (c == '-') {
                auto curr_size_V = V.rows();
                draw7(V,F,C);
                for (Eigen::Index r=curr_size_V; r<V.rows(); r++) {
                        V.row(r) += offset.transpose();
                }                
        }
        else if (c == '.') {
                auto curr_size_V = V.rows();
                draw_dot(V,F,C);
                for (Eigen::Index r=curr_size_V; r<V.rows(); r++) {
                        V.row(r) += offset.transpose();
                }                
        }
                
}
