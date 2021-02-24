#include "render/TextRenderer.h"

template<typename Font>
TextRenderer<Font> TextRenderer<Font>::
operator<< (const double& val_in) {
        std::stringstream ss;
        ss.precision(2);
        ss << std::fixed << val_in;
        if (data.length() > 0) data.append("\t");
        data.append(ss.str());
        return *this;
}

template TextRenderer<Digital> TextRenderer<Digital>::operator<< (const double& val_in);

template<typename Font>
void TextRenderer<Font>::render(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C)
{
        Point offset = center;
        for (const auto& c:data) {
                font_.draw(c, offset, V, F, C);
                offset += font_.glyph_width(c)*direction;
        }
}

template void TextRenderer<Digital>::render(Eigen::Matrix<double, Eigen::Dynamic, 3>& V, Eigen::Matrix<int,Eigen::Dynamic,3>& F, Eigen::Matrix<double,Eigen::Dynamic,3>& C);
