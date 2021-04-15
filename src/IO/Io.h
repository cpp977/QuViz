#ifndef QUVIZ_IO_H_
#define QUVIZ_IO_H_

#include <filesystem>
#include <iostream>
#include <fstream>

#include <boost/algorithm/string.hpp>

#include "util/HDF5Interface.h"

namespace IO {
enum class LOAD_MODE
{
    ROMAN = 0,
    HDF5 = 1
};

struct LoadInfos
{
    LoadInfos(const LOAD_MODE ldm_in, const std::string& obsname_in = "", const std::string& grpname_in = "")
        : ldm(ldm_in)
        , obsname(obsname_in)
        , grpname(grpname_in)
    {}
    LOAD_MODE ldm;
    std::string obsname;
    std::string grpname;
    std::function<std::size_t(const std::size_t)> num_map = [](const std::size_t i) { return i; };
};

std::pair<Eigen::VectorXi, Eigen::VectorXd> loadSiteObs(const std::string& filename, const LoadInfos li = LoadInfos(LOAD_MODE::ROMAN));

std::tuple<Eigen::VectorXi, Eigen::VectorXi, Eigen::VectorXd> loadBondObs(const std::string& filename,
                                                                          const LoadInfos li = LoadInfos(LOAD_MODE::ROMAN));

std::map<std::size_t, std::size_t> loadVertexMap(const std::string& filename);
} // namespace IO
#endif
