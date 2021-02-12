#ifndef RGB_H_
#define RGB_H_

#include "Eigen/Dense"

struct RGB
{
        constexpr RGB() : r(0.), g(0.), b(0.) {}
        constexpr RGB(const double r_in, const double g_in, const double b_in) : r(r_in), g(g_in), b(b_in) {}
        
        Eigen::Vector3d toEigen() const {
                Eigen::Vector3d out = {r,g,b};
                return out;
        }
        
        double r;
        double g;
        double b;
};
#endif
