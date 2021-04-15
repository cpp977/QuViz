#include "SOD20.h"

// const std::map<std::size_t, std::size_t> SOD20::schlegel_map_i = {
//         {8,0},{4,1},{9,2},{6,3},
//         {2,4},{0,5},{1,6},{3,7},
//         {7,8},{10,9},{5,10},{11,11},
//         {15,12},{12,13},{13,14},{14,15},
//         {19,16},{16,17},{17,18},{18,19}
// };

// const std::map<std::size_t, std::size_t> SOD20::schlegel_map = {
//         {0,8},{1,4},{2,9},{3,6},
//         {4,2},{5,0},{6,1},{7,3},
//         {8,7},{9,10},{10,5},{11,11},
//         {12,15},{13,12},{14,13},{15,14},
//         {16,19},{17,16},{18,17},{19,18}
// };

const std::map<std::size_t, std::size_t> SOD20::spiral_map_i = {{5, 0},   {11, 1},  {6, 2},  {9, 3},   {13, 4}, {4, 5},   {16, 6},
                                                                {3, 7},   {14, 8},  {18, 9}, {0, 10},  {8, 11}, {12, 12}, {10, 13},
                                                                {17, 14}, {15, 15}, {1, 16}, {19, 17}, {7, 18}, {2, 19}};

const std::map<std::size_t, std::size_t> SOD20::spiral_map = {{0, 5},   {1, 11},  {2, 6},  {3, 9},   {4, 13}, {5, 4},   {6, 16},
                                                              {7, 3},   {8, 14},  {9, 18}, {10, 0},  {11, 8}, {12, 12}, {13, 10},
                                                              {14, 17}, {15, 15}, {16, 1}, {17, 19}, {18, 7}, {19, 2}};

void SOD20::initializeVertexMap(const QuViz::MapType& opt, const std::string& filename)
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

const std::array<std::vector<int>, 30> SOD20::faces = {
    std::vector<int>{0, 5, 1, 4},   std::vector<int>{0, 8, 2, 10}, std::vector<int>{7, 2, 6, 3},
    std::vector<int>{7, 11, 5, 10}, std::vector<int>{9, 1, 11, 3}, std::vector<int>{9, 6, 8, 4},

    std::vector<int>{0, 4, 12}, /*12*/
    std::vector<int>{0, 12, 8}, /*12*/
    std::vector<int>{4, 8, 12}, /*12*/

    std::vector<int>{1, 5, 17}, /*17*/
    std::vector<int>{1, 17, 11}, /*17*/
    std::vector<int>{5, 11, 17}, /*17*/

    std::vector<int>{2, 7, 19}, /*19*/
    std::vector<int>{2, 19, 10}, /*19*/
    std::vector<int>{7, 10, 19}, /*19*/

    std::vector<int>{3, 6, 14}, /*14*/
    std::vector<int>{3, 14, 9}, /*14*/
    std::vector<int>{6, 9, 14}, /*14*/

    std::vector<int>{4, 1, 13}, /*13*/
    std::vector<int>{4, 13, 9}, /*13*/
    std::vector<int>{1, 9, 13}, /*13*/

    std::vector<int>{5, 0, 16}, /*16*/
    std::vector<int>{5, 16, 10}, /*16*/
    std::vector<int>{0, 10, 16}, /*16*/

    std::vector<int>{6, 2, 15}, /*15*/
    std::vector<int>{6, 15, 8}, /*15*/
    std::vector<int>{2, 8, 15}, /*15*/

    std::vector<int>{7, 3, 18}, /*18*/
    std::vector<int>{7, 18, 11}, /*18*/
    std::vector<int>{3, 11, 18} /*18*/
};
