#ifndef FONT_OPTIONS_H_
#define FONT_OPTIONS_H_

#include "vivid/color.h"

struct FontOptions
{
        double size=0.2;
        bool bold=false;
        bool italic=false;
        vivid::Color color = vivid::Color("black");
};
#endif
