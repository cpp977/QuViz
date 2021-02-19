#ifndef QUVIZ_IO_H_
#define QUVIZ_IO_H_

#include <filesystem>
#include <iostream>
#include <fstream>

#include <boost/algorithm/string.hpp>

namespace IO {
        enum class LOAD_MODE {
                ROMAN=0
        };
        
        std::pair<Eigen::VectorXi, Eigen::VectorXd>  loadSiteObs(const std::string& filename,  const LOAD_MODE ld = LOAD_MODE::ROMAN) {
                std::filesystem::path p(filename);
                assert(std::filesystem::exists(p) and "IO failure. File does ot exist.");

                std::ifstream stream(p.string(), std::ios::in);
                auto number_of_lines = std::count(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>(), '\n');
                stream.close();
                Eigen::VectorXi pos(number_of_lines);
                Eigen::VectorXd val(number_of_lines);
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

                return std::make_pair(pos,val);
        }

        std::tuple<Eigen::VectorXi, Eigen::VectorXi, Eigen::VectorXd>  loadBondObs(const std::string& filename,  const LOAD_MODE ld = LOAD_MODE::ROMAN) {
                std::filesystem::path p(filename);
                assert(std::filesystem::exists(p) and "IO failure. File does not exist.");

                std::ifstream stream(p.string(), std::ios::in);
                auto number_of_lines = std::count(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>(), '\n');
                stream.close();
                Eigen::VectorXi start(number_of_lines);
                Eigen::VectorXi end(number_of_lines);
                Eigen::VectorXd val(number_of_lines);
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
                return std::make_tuple(start,end,val);
        }

}
#endif
