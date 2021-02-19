#ifndef POLYGON_H_
#define POLYGON_H_

#include "Surface.h"

class Polygon : public Surface
{
public:
        Polygon(const std::size_t N_in, const double r_in, const double angle_in = 0.,
                const Point& center_in=Eigen::Vector3d::Zero(), const Point& normal_in=Eigen::Vector3d::UnitZ(), const vivid::Color& color_in=vivid::Color(QUVIZ_DEFAULT_COLOR)) :
                Surface(angle_in, center_in, normal_in, color_in), N(N_in), r(r_in) {};

        Polygon(const std::vector<Point>& p_in, const vivid::Color& color_in=vivid::Color(QUVIZ_DEFAULT_COLOR)) : Surface(0.,Eigen::Vector3d::Zero(),Eigen::Vector3d::Zero(),color_in) {
                N = p_in.size();
                assert(N>2 and "A polygon has to have more than two vertices");
                Eigen::ArrayXd distances(N-1);
                for (std::size_t i=1; i<N; i++) {distances(i-1) = (p_in[0]-p_in[i]).norm();}
                double a = distances.minCoeff();
                r = 0.5*a/std::sin(M_PI/N);
                points.resize(N);
                points[0] = p_in[0];
                std::vector<std::size_t> used_indices;
                used_indices.push_back(0);
                std::size_t index;
                for (std::size_t i=1; i<N; i++) {
                        for (std::size_t j=0; j<N; j++) {
                                if (auto it = std::find(used_indices.begin(), used_indices.end(), j); it != used_indices.end()) {continue;}
                                if (std::abs((points[i-1]-p_in[j]).norm()-a) < 1.e-10) {
                                        index = j;
                                        used_indices.push_back(j);
                                        break;
                                }
                        }
                        points[i] = p_in[index];
                }
        }
        
        virtual void draw(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const;

protected:
        std::size_t N;
        double r;
        std::vector<Point> points;
};
#endif

                // Point P1 = p_in[0];
                // Point P2 = p_in[1];
                // Point P3 = p_in[2];
                // Point S1 = P1-P2;
                // Point S2 = P1-P3;
                // normal = S1.cross(S2);
                // assert(normal.norm() > 1.e-10 and "Three of the points of the polygon lay on the same line.");
                // normal /= normal.norm();
                // // std::cout << "normal: " << normal.transpose() << std::endl;
                // double offset = -P1.dot(normal);
                // for (std::size_t i=3; i<p_in.size(); i++) {
                //         assert(std::abs(p_in[i].dot(normal)+offset) < 1.e-10 and "Not all points of the polygon lay on te same plane.");
                // }
                // std::vector<Point> transformed_to_0;
                // std::vector<Point> transformed_to_xyplane;
                
                // if (N%2 == 0) {
                //         std::vector<double> distances(N-1);
                //         for (std::size_t i=1; i<N; i++) {distances[i-1] = (P1-p_in[i]).norm();}
                //         std::size_t max_distance = std::distance(distances.begin(), std::max_element(distances.begin(), distances.end()));
                //         Point P2 = p_in[max_distance+1];
                //         center = P1 + 0.5*(P2-P1);
                //         r = (P1-center).norm();
                //         for (const auto& p: p_in) {transformed_to_0.push_back(p-center);}
                //         // for (const auto& p: transformed_to_0) {std::cout << p.transpose() << std::endl;} std::cout << std::endl;
                //         Point rot_axis = normal.cross(Eigen::Vector3d::UnitZ());

                //         if (rot_axis.norm()>1.e-10) {
                //                 rot_axis /= rot_axis.norm();
                //                 double r_angle = std::acos(Eigen::Vector3d::UnitZ().dot(normal));
                //                 std::cout << "angle between normal and Z: " << 180*r_angle/M_PI << std::endl;
                //                 Eigen::Matrix3d rot;
                //                 rot = Eigen::AngleAxisd(r_angle, rot_axis);

                //                 for (const auto& p: transformed_to_0) {transformed_to_xyplane.push_back(rot*p);}
                //         }
                //         else {transformed_to_xyplane = transformed_to_0;}
                //         for (const auto& p: transformed_to_xyplane) {assert(std::abs(p(2))<1.e-10);}
                //         angle = -std::acos(transformed_to_xyplane[0].dot(Eigen::Vector3d::UnitY())/transformed_to_xyplane[0].norm());
                //         std::cout << "angle in plane=" << 180*angle/M_PI << std::endl;

                //         for (std::size_t i=0; i<N; i++) {
                //                 std::cout << "p0: " << transformed_to_xyplane[i].transpose() << std::endl;
                //                 Point check = Eigen::AngleAxisd(angle,Eigen::Vector3d::UnitZ()).toRotationMatrix() * (transformed_to_xyplane[i].norm()*Eigen::Vector3d::UnitY());
                //                 std::cout << "check: " << check.transpose() << std::endl;
                //         }
                        
                //         std::cout << "p0: " << transformed_to_0[0].transpose() << std::endl;
                //         Point rot_axis2 = normal.cross(Eigen::Vector3d::UnitZ());
                //         if (normal == -Eigen::Vector3d::UnitZ()) {rot_axis2 = Eigen::Vector3d::UnitX();}
                //         else {rot_axis2 /= rot_axis.norm();}
                //         Eigen::Matrix3d rot2;
                //         rot2 = Eigen::AngleAxisd(-std::acos(Eigen::Vector3d::UnitZ().dot(normal)), rot_axis2);

                //         Point check2 = rot2 * transformed_to_xyplane[0];
                //         std::cout << "check2: " << check2.transpose() << std::endl;
                // }
