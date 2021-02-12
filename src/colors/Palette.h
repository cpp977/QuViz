#ifndef PALETTE_H_
#define PALETTE_H_

#include "Eigen/Dense"

#include "RGB.h"

struct Palette
{
        static inline constexpr RGB red = {255./255.,48./255.,48./255.};
        static inline constexpr RGB blue = {67./255.,110./255.,238./255.};
        static inline constexpr RGB green = {102./255.,205./255.,0.};
        static inline constexpr RGB yellow = {255./255.,215./255.,0};
        static inline constexpr RGB purple = {145./255.,44./255.,238./255.};
        static inline constexpr RGB white = {255./255.,255./255.,255./255.};
        static inline constexpr RGB black = {0./255.,0./255.,0./255.};
        static inline constexpr RGB orange = {255./255.,165./255.,0./255.};
        static inline constexpr RGB grey = {169./255.,169./255.,169./255.};
        static inline constexpr RGB gray = {169./255.,169./255.,169./255.};

        struct cmap {
                cmap(const double min_in, const double max_in) : min(min_in),max(max_in) {}
                RGB operator() (const double val) const {
                        return data(normalize(val));
                }
                double normalize(const double val) const {
                        return (val-min)/(max-min);
                }
                double min,max;
                RGB data(const double val) const {
                        return RGB(val,0.,val);
                }
        };
};

#endif
