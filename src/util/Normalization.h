#ifndef NORMALIZATION_H_
#define NORMALIZATION_H_

namespace util {
        
struct Normalization {
        Normalization(const double min_in, const double max_in) : min(min_in),max(max_in) {}
        double min,max;
        double operator() (const double val) const {
                return (val-min)/(max-min);
        }
};

}
#endif
