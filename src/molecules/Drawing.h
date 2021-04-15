#ifndef MOL_DRAWING_H_
#define MOL_DRAWING_H_

#include "util/Normalization.h"
#include "shapes/Polygon.h"
#include "vivid/vivid.h"

namespace Mol {
template <typename Molecule>
void drawVertices(Molecule& mol,
                  Eigen::Matrix<double, Eigen::Dynamic, 3>& V,
                  Eigen::Matrix<int, Eigen::Dynamic, 3>& F,
                  Eigen::Matrix<double, Eigen::Dynamic, 3>& C)
{
    assert(mol.colors_v.size() == 0 or mol.colors_v.size() == mol.vertices.size() or mol.colors_v.size() == 1);
    // draw black vertices if color is not given.
    if(mol.colors_v.size() == 0) {
        mol.colors_v.resize(mol.vertices.size());
        std::fill(mol.colors_v.begin(), mol.colors_v.end(), vivid::Color("black"));
    }
    if(mol.colors_v.size() == 1) {
        auto c = mol.colors_v[0];
        mol.colors_v.resize(mol.vertices.size());
        std::fill(mol.colors_v.begin(), mol.colors_v.end(), c);
    }

    std::vector<Sphere> sps;
    for(std::size_t i = 0; i < mol.vertices.size(); i++) {
        Point v(mol.vertices[mol.vertex_map.at(i)].data());
        sps.push_back(Sphere(mol.vertex_diameter, v, mol.colors_v[i]));
    }
    std::for_each(sps.begin(), sps.end(), [&V, &F, &C](const Sphere& s) { s.draw(V, F, C); });
}

template <typename Molecule>
void drawFaces(Molecule& mol,
               Eigen::Matrix<double, Eigen::Dynamic, 3>& V,
               Eigen::Matrix<int, Eigen::Dynamic, 3>& F,
               Eigen::Matrix<double, Eigen::Dynamic, 3>& C)
{
    assert(mol.colors_f.size() == 0 or mol.colors_f.size() == mol.faces.size() or mol.colors_f.size() == 1);
    // draw black vertices if color is not given.
    if(mol.colors_f.size() == 0) {
        mol.colors_f.resize(mol.faces.size());
        std::fill(mol.colors_f.begin(), mol.colors_f.end(), vivid::Color("grey"));
    }
    // set constant color if one color is given.
    if(mol.colors_f.size() == 1) {
        auto c = mol.colors_f[0];
        mol.colors_f.resize(mol.colors_f.size());
        std::fill(mol.colors_f.begin(), mol.colors_f.end(), c);
    }

    std::vector<std::vector<Point>> faces_points(mol.faces.size());
    for(std::size_t j = 0; j < mol.faces.size(); j++) {
        for(std::size_t i = 0; i < mol.faces[j].size(); i++) {
            Point h(mol.vertices[mol.faces[j][i]].data());
            faces_points[j].push_back(h);
        }
    }

    std::vector<Polygon> ps;
    for(std::size_t i = 0; i < mol.faces.size(); i++) { ps.push_back(Polygon(faces_points[i], mol.colors_f[i])); }
    std::for_each(ps.begin(), ps.end(), [&V, &F, &C](const Polygon& p) { p.draw(V, F, C); });
}

template <typename Molecule>
void drawEdges(Molecule& mol,
               Eigen::Matrix<double, Eigen::Dynamic, 3>& V,
               Eigen::Matrix<int, Eigen::Dynamic, 3>& F,
               Eigen::Matrix<double, Eigen::Dynamic, 3>& C)
{
    assert(mol.colors_e.size() == 0 or mol.colors_e.size() == mol.edges.size() or mol.colors_e.size() == 1);
    // draw black vertices if color is not given.
    if(mol.colors_e.size() == 0) {
        mol.colors_e.resize(mol.edges.size());
        std::fill(mol.colors_e.begin(), mol.colors_e.end(), vivid::Color("black"));
    }
    // set constant color if one color is given.
    if(mol.colors_e.size() == 1) {
        auto c = mol.colors_e[0];
        mol.colors_e.resize(mol.edges.size());
        std::fill(mol.colors_e.begin(), mol.colors_e.end(), c);
    }

    std::vector<std::array<Point, 2>> edges_points(mol.edges.size());
    for(std::size_t j = 0; j < mol.edges.size(); j++) {
        Point start(mol.vertices[mol.vertex_map.at(mol.edges[j][0])].data());
        Point end(mol.vertices[mol.vertex_map.at(mol.edges[j][1])].data());
        edges_points[j][0] = start;
        edges_points[j][1] = end;
    }

    std::vector<Tube> ts;
    for(std::size_t i = 0; i < mol.edges.size(); i++) {
        ts.push_back(Tube(mol.edge_diameter, edges_points[i][0], edges_points[i][1], mol.colors_e[i]));
    }
    std::for_each(ts.begin(), ts.end(), [&V, &F, &C](const Tube& t) { t.draw(V, F, C); });
}

template <typename Molecule>
void plotSiteObs(Molecule& mol,
                 const Eigen::VectorXi& pos,
                 const Eigen::VectorXd& obs,
                 const util::Normalization& norm,
                 Eigen::Matrix<double, Eigen::Dynamic, 3>& V,
                 Eigen::Matrix<int, Eigen::Dynamic, 3>& F,
                 Eigen::Matrix<double, Eigen::Dynamic, 3>& C,
                 vivid::ColorMap::Preset map_in = vivid::ColorMap::Preset::Turbo)
{
    assert(obs.size() == mol.vertices.size() and pos.size() == obs.size() and "No valid data for site observable.");

    std::vector<vivid::Color> colv(mol.vertices.size());
    vivid::ColorMap map(map_in);
    for(std::size_t i = 0; i < mol.vertices.size(); i++) { colv[pos(i)] = map.at(norm(obs(i))); }
    mol.colors_v = colv;
    drawVertices(mol, V, F, C);
}

template <typename Molecule>
void plotSiteObs(Molecule& mol,
                 const Eigen::VectorXi& pos,
                 const Eigen::VectorXd& obs,
                 Eigen::Matrix<double, Eigen::Dynamic, 3>& V,
                 Eigen::Matrix<int, Eigen::Dynamic, 3>& F,
                 Eigen::Matrix<double, Eigen::Dynamic, 3>& C,
                 vivid::ColorMap::Preset map_in = vivid::ColorMap::Preset::Turbo)
{
    return plotSiteObs(mol, pos, obs, util::Normalization(obs.minCoeff(), obs.maxCoeff()), V, F, C, map_in);
}

template <typename Molecule>
void plotBondObs(Molecule& mol,
                 const Eigen::VectorXi& start,
                 const Eigen::VectorXi& end,
                 const Eigen::VectorXd& obs,
                 const util::Normalization& norm,
                 Eigen::Matrix<double, Eigen::Dynamic, 3>& V,
                 Eigen::Matrix<int, Eigen::Dynamic, 3>& F,
                 Eigen::Matrix<double, Eigen::Dynamic, 3>& C,
                 vivid::ColorMap::Preset map_in = vivid::ColorMap::Preset::Turbo)
{
    // assert(obs.size() == mol.edges.size() and "No valid data for edge observable.");
    assert(start.size() == end.size() and "No valid data for edge observable.");
    assert(start.size() == obs.size() and "No valid data for edge observable.");
    mol.edges.clear();
    mol.edges.resize(start.size());
    for(std::size_t i = 0; i < mol.edges.size(); i++) {
        // for(std::size_t i = 0; i < 10; i++) {
        mol.edges[i][0] = start(i);
        mol.edges[i][1] = end(i);
    }
    std::vector<vivid::Color> cole(mol.edges.size());
    vivid::ColorMap map(map_in);
    for(std::size_t i = 0; i < mol.edges.size(); i++) { cole[i] = map.at(norm(obs(i))); }
    mol.colors_e = cole;
    drawEdges(mol, V, F, C);
}

template <typename Molecule>
void plotBondObs(Molecule& mol,
                 const Eigen::VectorXi& start,
                 const Eigen::VectorXi& end,
                 const Eigen::VectorXd& obs,
                 Eigen::Matrix<double, Eigen::Dynamic, 3>& V,
                 Eigen::Matrix<int, Eigen::Dynamic, 3>& F,
                 Eigen::Matrix<double, Eigen::Dynamic, 3>& C,
                 vivid::ColorMap::Preset map_in = vivid::ColorMap::Preset::Turbo)
{
    return plotBondObs(mol, start, end, obs, util::Normalization(obs.minCoeff(), obs.maxCoeff()), V, F, C);
}

} // namespace Mol
#endif
