#ifndef QUVIZ_IO_H_
#define QUVIZ_IO_H_

#include <filesystem>
#include <iostream>
#include <fstream>

#include <boost/algorithm/string.hpp>

#include "util/HDF5Interface.h"

namespace IO {
        enum class LOAD_MODE {
                ROMAN=0,
                HDF5=1
        };

        struct LoadInfos {
                LoadInfos(const LOAD_MODE ldm_in, const std::string& obsname_in="", const std::string& grpname_in="") : ldm(ldm_in), obsname(obsname_in), grpname(grpname_in) {}
                LOAD_MODE ldm;
                std::string obsname;
                std::string grpname;
        };
        
        std::pair<Eigen::VectorXi, Eigen::VectorXd>  loadSiteObs(const std::string& filename, const LoadInfos li = LoadInfos(LOAD_MODE::ROMAN)) {
                std::filesystem::path p(filename);
                assert(std::filesystem::exists(p) and "IO failure. File does ot exist.");

                Eigen::VectorXi pos;
                Eigen::VectorXd val;
                if ( li.ldm == LOAD_MODE::ROMAN) {
                        std::ifstream stream(p.string(), std::ios::in);
                        auto number_of_lines = std::count(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>(), '\n');
                        stream.close();
                        pos.resize(number_of_lines);
                        val.resize(number_of_lines);
                        std::size_t index=0;
                        std::string line;
                        stream.open(p.string(), std::ios::in);
                        if (stream.is_open()) {
                                while ( std::getline(stream,line) ) {
                                        std::vector<std::string> results;
                                
                                        boost::split(results, line, [](char c){return c == '\t';});
                                        pos(index) = stoi(results[0]);
                                        val(index) = stod(results[1]);
                                        index++;
                                }
                                stream.close();
                        }
                }
                else if(li.ldm == LOAD_MODE::HDF5) {
                        assert(HDF5Interface::IS_VALID_HDF5(filename) and "Hdf5 file seems to be broken");
                        HDF5Interface source(filename, FILE_ACCESS_MODE::READ);
                        source.load_vector(val, li.obsname, li.grpname);
                        pos.resize(val.size());
                        for (int i=0; i<val.size(); i++) {pos(i) = i;}
                
                }
                return std::make_pair(pos,val);
        }

        std::tuple<Eigen::VectorXi, Eigen::VectorXi, Eigen::VectorXd>  loadBondObs(const std::string& filename, const LoadInfos li = LoadInfos(LOAD_MODE::ROMAN)) {
                std::filesystem::path p(filename);
                assert(std::filesystem::exists(p) and "IO failure. File does not exist.");

                Eigen::VectorXi start;
                Eigen::VectorXi end;
                Eigen::VectorXd val;

                if (li.ldm == LOAD_MODE::ROMAN) {
                        std::ifstream stream(p.string(), std::ios::in);
                        auto number_of_lines = std::count(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>(), '\n');
                        stream.close();
                        start.resize(number_of_lines);
                        end.resize(number_of_lines);
                        val.resize(number_of_lines);
                        std::size_t index=0;
                        std::string line;
                        stream.open(p.string(), std::ios::in);
                        if (stream.is_open()) {
                                while ( std::getline(stream,line) ) {
                                        std::vector<std::string> results;
                                
                                        boost::split(results, line, [](char c){return c == '\t';});
                                        if (results[0].find("#") != std::string::npos) {
                                                assert(index==0 and "Input file contains unknown characters.");
                                                start.resize(number_of_lines-1);
                                                end.resize(number_of_lines-1);
                                                val.resize(number_of_lines-1);
                                                continue;
                                        } //skip first line if necessary
                                        // for (const auto& res:results) {std::cout << res << " ";} std::cout << std::endl;
                                        start(index) = stoi(results[0]);
                                        end(index) = stoi(results[1]);
                                        val(index) = stod(results[2]);
                                        index++;
                                }
                                stream.close();
                        }
                }
                else if (li.ldm == LOAD_MODE::HDF5) {
                        assert(HDF5Interface::IS_VALID_HDF5(filename) and "Hdf5 file seems to be broken");
                        HDF5Interface source(filename, FILE_ACCESS_MODE::READ);

                        if (li.obsname.find("n_") != std::string::npos) {
                                Eigen::MatrixXi coords;
                                source.load_matrix(coords, "n_coords", li.grpname);
                                std::size_t number_of_bonds = (coords.array()!=-1).count();
                                val.resize(number_of_bonds);
                                start.resize(number_of_bonds);
                                end.resize(number_of_bonds);
                                Eigen::MatrixXd tmp;
                                source.load_matrix(tmp, li.obsname, li.grpname);
                                std::size_t index=0;
                                for (std::size_t row=0; row<coords.rows(); row++)
                                for (std::size_t col=0; col<coords.cols(); col++) {
                                        if (coords(row,col) != -1) {
                                                val(index) = tmp(row,col);
                                                start(index) = row;
                                                end(index) = coords(row,col);
                                                index++;
                                        }
                                }
                        }
                        else {
                                Eigen::MatrixXd tmp;
                                source.load_matrix(tmp, li.obsname, li.grpname);
                                val.resize(tmp.size());
                                start.resize(val.size());
                                end.resize(val.size());
                                                
                                for (std::size_t row=0; row<tmp.rows(); row++)
                                        for (std::size_t col=0; col<tmp.cols(); col++) {
                                                val(row*tmp.cols()+col) = tmp(row,col);
                                                start(row*tmp.cols()+col) = row;
                                                if (tmp.cols() == 1) {end(row*tmp.cols()+col) = row;}
                                                else {end(row*tmp.cols()+col) = col;}
                                
                                        }
                        }
                        source.close();
                }
                return std::make_tuple(start,end,val);
        }

}
#endif
