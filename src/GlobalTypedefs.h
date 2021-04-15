#ifndef GLOBAL_TYPEDEFS_H_
#define GLOBAL_TYPEDEFS_H_
#include "Eigen/Dense"

typedef Eigen::Vector3d Point;

namespace QuViz {
enum class MapType
{
    Spiral,
    Cuthill,
    Identity,
    FromFile
};
}

#endif
