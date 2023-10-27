#ifndef EXPORT_H_
#define EXPORT_H_

#include "gifanim.h"

namespace FileFormats {
        struct GifOptions {
                int width=640, height=480, framedelay=100, loopcount=0, bitdepth=8;
                bool dipher = false;
        };

        struct PNGOptions {
                int width=640, height=480;
        };
}

namespace Export {
        void GIF(const std::string& filename, const FileFormats::GifOptions& gifOptions, const int& num_pngs, const Eigen::Vector3d& axis, igl::embree::EmbreeRenderer& er) {
                int width=gifOptions.width;
                int height=gifOptions.height;

                GifAnim ganim;
                GifWriter g;
                ganim.GifBegin(&g, filename.c_str(), width, height, gifOptions.framedelay, gifOptions.loopcount, gifOptions.bitdepth, gifOptions.dipher);
                double delta_angle = 2.*M_PI/num_pngs;
                for (int i=0; i<num_pngs; i++) {
                        // Allocate temporary buffers
                        Eigen::Matrix<unsigned char,Eigen::Dynamic,Eigen::Dynamic> R(gifOptions.width,gifOptions.height);
                        Eigen::Matrix<unsigned char,Eigen::Dynamic,Eigen::Dynamic> G(gifOptions.width,gifOptions.height);
                        Eigen::Matrix<unsigned char,Eigen::Dynamic,Eigen::Dynamic> B(gifOptions.width,gifOptions.height);
                        Eigen::Matrix<unsigned char,Eigen::Dynamic,Eigen::Dynamic> A(gifOptions.width,gifOptions.height);
                
                        // Draw the scene in the buffers
                        er.render_buffer(R,G,B,A);

                        const int comp = 4;                                  // 4 Channels Red, Green, Blue, Alpha
                        std::vector<uint8_t> image(R.size()*comp,0);     // The image itself;

                        for (unsigned i = 0; i<R.rows();++i) {
                                for (unsigned j = 0; j < R.cols(); ++j) {
                                        image[(j * R.rows() * comp) + (i * comp) + 0] = R(i,R.cols()-1-j);
                                        image[(j * R.rows() * comp) + (i * comp) + 1] = G(i,R.cols()-1-j);
                                        image[(j * R.rows() * comp) + (i * comp) + 2] = B(i,R.cols()-1-j);
                                        image[(j * R.rows() * comp) + (i * comp) + 3] = A(i,R.cols()-1-j);
                                }
                        }

                        ganim.GifWriteFrame(&g, image.data(), gifOptions.width, gifOptions.height, gifOptions.framedelay, gifOptions.bitdepth, gifOptions.dipher);

                        Eigen::Matrix3d rot;
                        rot = Eigen::AngleAxisd(i*delta_angle,axis);
                        er.set_rot(rot);
                        // viewer.core().camera_eye = rot * viewer.core().camera_eye;

                }
                ganim.GifEnd(&g);
        }

        void PNG(const std::string& filename, const FileFormats::PNGOptions& pngOptions, const double& angle, const double& zoom, const Eigen::Vector3d& axis, igl::embree::EmbreeRenderer& er) {
                Eigen::Matrix<unsigned char,Eigen::Dynamic,Eigen::Dynamic> R(pngOptions.width,pngOptions.height);
                Eigen::Matrix<unsigned char,Eigen::Dynamic,Eigen::Dynamic> G(pngOptions.width,pngOptions.height);
                Eigen::Matrix<unsigned char,Eigen::Dynamic,Eigen::Dynamic> B(pngOptions.width,pngOptions.height);
                Eigen::Matrix<unsigned char,Eigen::Dynamic,Eigen::Dynamic> A(pngOptions.width,pngOptions.height);

				Eigen::Matrix3d rot;
				rot = Eigen::AngleAxisd(angle, axis);
				er.set_rot(rot);
				er.set_zoom(zoom);
                // Draw the scene in the buffers
                er.render_buffer(R,G,B,A);

                // save to PNG file
                igl::stb::write_image(filename,R,G,B,A,0);
        }

}

#endif
