#include <iostream>

#include "Eigen/Geometry"

#include "Polygon.h"

void Polygon::draw(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const
{
        auto curr_size_V = V.rows();
        V.conservativeResize(curr_size_V+N+1,3);

        if (points.size() > 0) {
                Point center = points[0] + r*((points[1]-points[0]) + points[N-1]-points[0])/((points[1]-points[0]) + points[N-1]-points[0]).norm();
                V.row(curr_size_V) = center;
                for (std::size_t n=0; n<N; n++) {
                        V.row(curr_size_V+1+n) = points[n];
                }
        }
        else {
                double rot_angle = 2*M_PI/N;
                std::vector<Point> ps(N+1);
                ps[0] = Eigen::Vector3d::Zero();
                ps[1] = r*Eigen::Vector3d::UnitY();
                for (std::size_t n=2; n<N+1; n++) {
                        ps[n] = Eigen::AngleAxisd(rot_angle, Eigen::Vector3d::UnitZ()) * ps[n-1];
                }
                for (std::size_t n=0; n<N+1; n++) {
                        V.row(curr_size_V+n) = ps[n];
                }
        }
        auto curr_size_F = F.rows();
        F.conservativeResize(curr_size_F+N,3);
        for (std::size_t n=0; n<N-1; n++) {
                F.row(curr_size_F+n) << curr_size_V+1+n, curr_size_V+1+n+1, curr_size_V+0;
        }
        F.row(curr_size_F+N-1) << curr_size_V+1+N-1, curr_size_V+1, curr_size_V+0;
        
        auto curr_size_C = C.rows();
        C.conservativeResize(curr_size_C+N,3);
        for (Eigen::Index r=curr_size_C; r<C.rows(); r++) {
                C.row(r) = color.toEigen();
        }
        
        if (points.size() == 0) {
                this->rotate(V, curr_size_V, N+1);
                this->translate(V, curr_size_V, N+1);
        }
}
