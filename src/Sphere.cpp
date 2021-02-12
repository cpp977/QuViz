#include <iostream>

#include "Eigen/Geometry"

#include "Sphere.h"

void Sphere::draw(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const
{
        std::size_t Nphi=30;
        std::size_t Ntheta=30;
        
        auto curr_size_V = V.rows();
        V.conservativeResize(curr_size_V+2+Nphi*(Ntheta-1),3);

        auto cartesian = [this] (double theta, double phi) -> Point {
                Point out = Eigen::Vector3d::Zero();
                out[0] = r*std::sin(theta)*std::cos(phi);
                out[1] = r*std::sin(theta)*std::sin(phi);
                out[2] = r*std::cos(theta);
                return out;
        };

        V.row(curr_size_V+0) = r*Eigen::Vector3d::UnitZ(); //top
        for (std::size_t ntheta=1; ntheta<Ntheta; ntheta++) {
                double theta = (ntheta*M_PI)/Ntheta;
                for (std::size_t nphi=0; nphi<Nphi; nphi++) {
                        double phi = (nphi*2*M_PI)/Nphi;
                        V.row(curr_size_V+(ntheta-1)*Nphi+nphi+1) = cartesian(theta, phi);
                }
        }
        V.row(curr_size_V+1+Nphi*(Ntheta-1)) = -r*Eigen::Vector3d::UnitZ(); //bottom

        //V[0] = top
        //V[0*Nphi+1,...,1*Nphi] = first equatorial circle
        //V[1*Nphi+1,...,2*Nphi] = second equatorial circle
        //V[2*Nphi+1,...,3*Nphi] = third equatorial circle
        //...
        //V[(Ntheta-2)*Nphi+1,...,(Ntheta-1)*Nphi] = (Ntheta-1) equatorial circle
        //V[(Ntheta-1)*Nphi+1] = bottom
        
        auto curr_size_F = F.rows();
        F.conservativeResize(curr_size_F+(Ntheta-1)*Nphi*2,3);

        for (std::size_t nphi=0; nphi<Nphi-1; nphi++) {
                F.row(curr_size_F+nphi) << curr_size_V, curr_size_V+1+nphi, curr_size_V+1+nphi+1;
        }
        F.row(curr_size_F+Nphi-1) << curr_size_V, curr_size_V+Nphi, curr_size_V+1;

        for (std::size_t ntheta=1; ntheta<Ntheta-1; ntheta++) {
                for (std::size_t nphi=0; nphi<Nphi-1; nphi++) {
                        F.row(curr_size_F+(2*ntheta-1)*Nphi+2*nphi) << curr_size_V+1+(ntheta)*Nphi+nphi, curr_size_V+1+(ntheta-1)*Nphi+nphi+1, curr_size_V+1+(ntheta-1)*Nphi+nphi;
                        F.row(curr_size_F+(2*ntheta-1)*Nphi+2*nphi+1) << curr_size_V+1+(ntheta)*Nphi+nphi+1, curr_size_V+1+(ntheta-1)*Nphi+nphi+1, curr_size_V+1+(ntheta)*Nphi+nphi;
                }
                F.row(curr_size_F+(2*ntheta-1)*Nphi+2*(Nphi-1)) << curr_size_V+1+(ntheta)*Nphi+Nphi-1, curr_size_V+1+(ntheta-1)*Nphi+0, curr_size_V+1+(ntheta-1)*Nphi+Nphi-1;
                F.row(curr_size_F+(2*ntheta-1)*Nphi+2*(Nphi-1)+1) << curr_size_V+1+(ntheta)*Nphi+0, curr_size_V+1+(ntheta-1)*Nphi+0, curr_size_V+1+(ntheta)*Nphi+Nphi-1;
        }

        for (std::size_t nphi=0; nphi<Nphi-1; nphi++) {
                F.row(curr_size_F+(2*(Ntheta-2)-1)*Nphi+2*Nphi+nphi) << curr_size_V+(Ntheta-2)*Nphi+1+nphi+1, curr_size_V+(Ntheta-2)*Nphi+1+nphi, curr_size_V+(Ntheta-1)*Nphi+1;
        }
        F.row(curr_size_F+(2*(Ntheta-2)-1)*Nphi+2*Nphi+Nphi-1) << curr_size_V+(Ntheta-2)*Nphi+1, curr_size_V+(Ntheta-2)*Nphi+Nphi, curr_size_V+(Ntheta-1)*Nphi+1;
        
        auto curr_size_C = C.rows();
        C.conservativeResize(curr_size_C+2*(Ntheta-1)*Nphi,3);
        for (Eigen::Index r=curr_size_C; r<C.rows(); r++) {
                C.row(r) = color.toEigen();
        }
        
        this->translate(V, curr_size_V, V.rows()-curr_size_V);
}
