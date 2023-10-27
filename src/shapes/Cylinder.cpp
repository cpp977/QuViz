#include <iostream>

#include "Eigen/Geometry"

#include "Cylinder.h"

void Cylinder::draw(Eigen::Matrix<double, Eigen::Dynamic, 3>& V,
                    Eigen::Matrix<int, Eigen::Dynamic, 3>& F,
                    Eigen::Matrix<double, Eigen::Dynamic, 3>& C) const
{
    std::size_t N = 30;

    double rot_angle = 2 * M_PI / N;

    auto curr_size_V = V.rows();
    V.conservativeResize(curr_size_V + 2 * N + 2, 3);

    std::vector<Point> ps_g(N + 1);
    ps_g[0] = -0.5 * h * Eigen::Vector3d::UnitZ();
    ps_g[1] = r * Eigen::Vector3d::UnitY() - 0.5 * h * Eigen::Vector3d::UnitZ();
    for(std::size_t n = 2; n < N + 1; n++) { ps_g[n] = Eigen::AngleAxisd(rot_angle, Eigen::Vector3d::UnitZ()) * ps_g[n - 1]; }

    std::vector<Point> ps_r(N + 1);
    ps_r[0] = +0.5 * h * Eigen::Vector3d::UnitZ();
    ps_r[1] = Eigen::AngleAxisd(-0.5 * rot_angle, Eigen::Vector3d::UnitZ()) * (r * Eigen::Vector3d::UnitY() + 0.5 * h * Eigen::Vector3d::UnitZ());
    for(std::size_t n = 2; n < N + 1; n++) { ps_r[n] = Eigen::AngleAxisd(rot_angle, Eigen::Vector3d::UnitZ()) * ps_r[n - 1]; }

    for(std::size_t n = 0; n < N + 1; n++) { V.row(curr_size_V + n) = ps_g[n]; }
    for(std::size_t n = 0; n < N + 1; n++) { V.row(curr_size_V + N + 1 + n) = ps_r[n]; }

    // V[0] = 0
    // V[1,...,N] = vertices ground
    // V[N+1] = 0
    // V[N+2,...,2N+1] = vertices roof

    auto curr_size_F = F.rows();

    if(DRAW_BASES) {
        F.conservativeResize(curr_size_F + 4 * N, 3);
        for(std::size_t n = 0; n < N - 1; n++) { F.row(curr_size_F + n) << curr_size_V + 0, curr_size_V + 1 + n + 1, curr_size_V + 1 + n; }
        F.row(curr_size_F + N - 1) << curr_size_V + 0, curr_size_V + 1, curr_size_V + 1 + N - 1;

        for(std::size_t n = 0; n < N - 1; n++) {
            F.row(curr_size_F + N + n) << curr_size_V + N + 2 + n, curr_size_V + N + 2 + n + 1, curr_size_V + N + 1;
        }
        F.row(curr_size_F + 2 * N - 1) << curr_size_V + 1 + 2 * N, curr_size_V + N + 2, curr_size_V + N + 1;

        for(std::size_t n = 0; n < N - 1; n++) {
            F.row(curr_size_F + 2 * N + n) << curr_size_V + n + 1, curr_size_V + N + 2 + n + 1, curr_size_V + N + 2 + n;
        }
        F.row(curr_size_F + 2 * N + N - 1) << curr_size_V + N, curr_size_V + N + 2, curr_size_V + 2 * N + 1;

        F.row(curr_size_F + 2 * N + N + 0) << curr_size_V + 1, curr_size_V + N + 2, curr_size_V + N;
        for(std::size_t n = 1; n < N; n++) {
            F.row(curr_size_F + 2 * N + N + n) << curr_size_V + n + 1, curr_size_V + N + 2 + n, curr_size_V + n + 1 - 1;
        }
    } else {
        F.conservativeResize(curr_size_F + 2 * N, 3);
        for(std::size_t n = 0; n < N - 1; n++) {
            F.row(curr_size_F + n) << curr_size_V + n + 1, curr_size_V + N + 2 + n + 1, curr_size_V + N + 2 + n;
        }
        F.row(curr_size_F + N - 1) << curr_size_V + N, curr_size_V + N + 2, curr_size_V + 2 * N + 1;

        F.row(curr_size_F + N + 0) << curr_size_V + 1, curr_size_V + N + 2, curr_size_V + N;
        for(std::size_t n = 1; n < N; n++) { F.row(curr_size_F + N + n) << curr_size_V + n + 1, curr_size_V + N + 2 + n, curr_size_V + n + 1 - 1; }
    }

    auto curr_size_C = C.rows();
    if(DRAW_BASES) {
        C.conservativeResize(curr_size_C + 4 * N, 3);
    } else {
        C.conservativeResize(curr_size_C + 2 * N, 3);
    }
    for(Eigen::Index r = curr_size_C; r < C.rows(); r++) { C.row(r) << color.value()[0], color.value()[1], color.value()[2]; }

    this->rotate(V, curr_size_V, V.rows() - curr_size_V);
    this->translate(V, curr_size_V, V.rows() - curr_size_V);
}
