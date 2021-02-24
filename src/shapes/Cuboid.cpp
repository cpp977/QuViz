#include <iostream>

#include "Eigen/Geometry"

#include "Rectangle.h"
#include "Cuboid.h"

void Cuboid::draw(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C) const
{
        Point unit1 = Eigen::Vector3d::UnitX();
        Point unit2 = Eigen::Vector3d::UnitY();
        Point unit3 = Eigen::Vector3d::UnitZ();

        
        Rectangle r1(b,a,color,0.,0.5*c*unit3,unit3);
        Rectangle r2(b,a,color,0.,-0.5*c*unit3,-unit3);
        Rectangle r3(a,c,color,0.,+0.5*b*unit2,unit2);
        Rectangle r4(a,c,color,0.,-0.5*b*unit2,-unit2);
        Rectangle r5(c,b,color,0.,+0.5*a*unit1,unit1);
        Rectangle r6(c,b,color,0.,-0.5*a*unit1,-unit1);
        
        auto curr_size_V = V.rows();
        r1.draw(V,F,C);
        r2.draw(V,F,C);
        r3.draw(V,F,C);
        r4.draw(V,F,C);
        r5.draw(V,F,C);
        r6.draw(V,F,C);
        
        this->rotate(V, curr_size_V, V.rows()-curr_size_V);
        this->translate(V, curr_size_V, V.rows()-curr_size_V);
}
