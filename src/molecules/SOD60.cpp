#include "SOD60.h"

const std::map<std::size_t, std::size_t> SOD60::spiral_map_i = {
    {34, 0},  {38, 1},  {56, 2},  {6, 3},   {2, 4},   {22, 5},  {18, 6},  {39, 7},  {26, 8},  {4, 9},   {36, 10}, {0, 11},
    {24, 12}, {59, 13}, {31, 14}, {23, 15}, {55, 16}, {29, 17}, {19, 18}, {48, 19}, {14, 20}, {12, 21}, {37, 22}, {32, 23},
    {45, 24}, {10, 25}, {8, 26},  {51, 27}, {15, 28}, {57, 29}, {35, 30}, {47, 31}, {11, 32}, {49, 33}, {30, 34}, {13, 35},
    {52, 36}, {20, 37}, {16, 38}, {44, 39}, {9, 40},  {28, 41}, {50, 42}, {27, 43}, {42, 44}, {7, 45},  {3, 46},  {46, 47},
    {25, 48}, {58, 49}, {21, 50}, {53, 51}, {17, 52}, {43, 53}, {5, 54},  {41, 55}, {1, 56},  {54, 57}, {33, 58}, {40, 59}};

const std::map<std::size_t, std::size_t> SOD60::spiral_map = {
    {0, 34},  {1, 38},  {2, 56},  {3, 6},   {4, 2},   {5, 22},  {6, 18},  {7, 39},  {8, 26},  {9, 4},   {10, 36}, {11, 0},
    {12, 24}, {13, 59}, {14, 31}, {15, 23}, {16, 55}, {17, 29}, {18, 19}, {19, 48}, {20, 14}, {21, 12}, {22, 37}, {23, 32},
    {24, 45}, {25, 10}, {26, 8},  {27, 51}, {28, 15}, {29, 57}, {30, 35}, {31, 47}, {32, 11}, {33, 49}, {34, 30}, {35, 13},
    {36, 52}, {37, 20}, {38, 16}, {39, 44}, {40, 9},  {41, 28}, {42, 50}, {43, 27}, {44, 42}, {45, 7},  {46, 3},  {47, 46},
    {48, 25}, {49, 58}, {50, 21}, {51, 53}, {52, 17}, {53, 43}, {54, 5},  {55, 41}, {56, 1},  {57, 54}, {58, 33}, {59, 40}};

void SOD60::initializeVertexMap(const QuViz::MapType& opt, const std::string& filename)
{
    if(opt == QuViz::MapType::Spiral) {
        vertex_map = spiral_map;
    } else if(opt == QuViz::MapType::Identity) {
        for(std::size_t i = 0; i < vertices.size(); i++) { vertex_map[i] = i; }
    } else if(opt == QuViz::MapType::FromFile) {
        vertex_map = IO::loadVertexMap(filename);
    } else {
        assert(false and "Unsupported option for QuViz::MapType");
    }
}

const std::array<std::vector<int>, 86> SOD60::faces = {
    std::vector<int>{0, 24, 8, 28, 16, 32},
    std::vector<int>{1, 33, 17, 28, 9, 25},
    std::vector<int>{2, 34, 18, 29, 10, 24},
    std::vector<int>{3, 25, 11, 29, 19, 35},
    std::vector<int>{4, 32, 20, 30, 12, 26},
    std::vector<int>{5, 27, 13, 30, 21, 33},
    std::vector<int>{6, 26, 14, 31, 22, 34},
    std::vector<int>{7, 35, 23, 31, 15, 27},
    std::vector<int>{0, 4, 6, 2},
    std::vector<int>{1, 3, 7, 5},
    std::vector<int>{8, 10, 11, 9},
    std::vector<int>{12, 13, 15, 14},
    std::vector<int>{16, 17, 21, 20},
    std::vector<int>{18, 22, 23, 19},

    std::vector<int>{36, 2, 24}, /*36*/
    std::vector<int>{0, 36, 24}, /*36*/
    std::vector<int>{0, 2, 36}, /*36*/

    std::vector<int>{37, 32, 4}, /*37*/
    std::vector<int>{0, 37, 4}, /*37*/
    std::vector<int>{0, 32, 37}, /*37*/

    std::vector<int>{38, 6, 34}, /*38*/
    std::vector<int>{2, 38, 34}, /*38*/
    std::vector<int>{2, 6, 38}, /*38*/

    std::vector<int>{39, 26, 6}, /*39*/
    std::vector<int>{4, 39, 6}, /*39*/
    std::vector<int>{4, 26, 39}, /*39*/

    std::vector<int>{40, 5, 33}, /*40*/
    std::vector<int>{1, 40, 33}, /*40*/
    std::vector<int>{1, 5, 40}, /*40*/

    std::vector<int>{41, 25, 3}, /*41*/
    std::vector<int>{1, 41, 3}, /*41*/
    std::vector<int>{1, 25, 41}, /*41*/

    std::vector<int>{42, 35, 7}, /*42*/
    std::vector<int>{3, 42, 7}, /*42*/
    std::vector<int>{3, 35, 42}, /*42*/

    std::vector<int>{43, 7, 27}, /*43*/
    std::vector<int>{5, 43, 27}, /*43*/
    std::vector<int>{5, 7, 43}, /*43*/

    std::vector<int>{44, 9, 28}, /*44*/
    std::vector<int>{8, 44, 28}, /*44*/
    std::vector<int>{8, 9, 44}, /*44*/

    std::vector<int>{45, 24, 10}, /*45*/
    std::vector<int>{8, 45, 10}, /*45*/
    std::vector<int>{8, 24, 45}, /*45*/

    std::vector<int>{46, 11, 25}, /*46*/
    std::vector<int>{9, 46, 25}, /*46*/
    std::vector<int>{9, 11, 46}, /*46*/

    std::vector<int>{47, 29, 11}, /*47*/
    std::vector<int>{10, 47, 11}, /*47*/
    std::vector<int>{10, 29, 47}, /*47*/

    std::vector<int>{48, 14, 26}, /*48*/
    std::vector<int>{12, 48, 26}, /*48*/
    std::vector<int>{12, 14, 48}, /*48*/

    std::vector<int>{49, 30, 13}, /*49*/
    std::vector<int>{12, 49, 13}, /*49*/
    std::vector<int>{12, 30, 49}, /*49*/

    std::vector<int>{50, 27, 15}, /*50*/
    std::vector<int>{13, 50, 15}, /*50*/
    std::vector<int>{13, 27, 50}, /*50*/

    std::vector<int>{51, 15, 31}, /*51*/
    std::vector<int>{14, 51, 31}, /*51*/
    std::vector<int>{14, 15, 51}, /*51*/

    std::vector<int>{52, 20, 32}, /*52*/
    std::vector<int>{16, 52, 32}, /*52*/
    std::vector<int>{16, 20, 52}, /*52*/

    std::vector<int>{53, 28, 17}, /*53*/
    std::vector<int>{16, 53, 17}, /*53*/
    std::vector<int>{16, 28, 53}, /*53*/

    std::vector<int>{54, 33, 21}, /*54*/
    std::vector<int>{17, 54, 21}, /*54*/
    std::vector<int>{17, 33, 54}, /*54*/

    std::vector<int>{55, 19, 29}, /*55*/
    std::vector<int>{18, 55, 29}, /*55*/
    std::vector<int>{18, 19, 55}, /*55*/

    std::vector<int>{56, 34, 22}, /*56*/
    std::vector<int>{18, 56, 22}, /*56*/
    std::vector<int>{18, 34, 56}, /*56*/

    std::vector<int>{57, 23, 35}, /*57*/
    std::vector<int>{19, 57, 35}, /*57*/
    std::vector<int>{19, 23, 57}, /*57*/

    std::vector<int>{58, 21, 30}, /*58*/
    std::vector<int>{20, 58, 30}, /*58*/
    std::vector<int>{20, 21, 58}, /*58*/

    std::vector<int>{59, 31, 23}, /*59*/
    std::vector<int>{22, 59, 23}, /*59*/
    std::vector<int>{22, 31, 59} /*59*/
};
