#ifndef TEXT_RENDERER_H_
#define TEXT_RENDERER_H_

#include <sstream>

#include "Eigen/Dense"

#include "GlobalTypedefs.h"

#include "fonts/Digital.h"
#include "fonts/FontOptions.h"

template<typename Font_>
class TextRenderer
{
public:
        typedef Font_ Font;
        
        TextRenderer(const Font& font_in, const Point& center_in=Eigen::Vector3d::Zero(), const Point& direction_in=Eigen::Vector3d::UnitX()) :
                font_(font_in), center(center_in), direction(direction_in) {}
        
        inline Font& font() {return font_;}
        inline Font font() const {return font_;}

        TextRenderer operator<< (const double& val_in);

        void render(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C);

        void set_center(const Point& new_center) {center=new_center;}
private:
        Font font_;
        Point center;
        Point direction;
        std::string data;
};

#endif
