#ifndef NORMALIZATION_H_
#define NORMALIZATION_H_

namespace util {

struct Normalization
{
    Normalization(const double min_in, const double max_in)
        : min(min_in)
        , max(max_in)
    {
        mid = 0.5 * (max + min);
    }
    Normalization(const double min_in, const double max_in, const double mid_in)
        : min(min_in)
        , max(max_in)
        , mid(mid_in)
    {}
    double min, max, mid;
    double operator()(const double val) const
    {
        if(val < mid) {
            return (val - min) / (2. * mid - 2. * min);
        } else {
            return (val - mid) / (2. * max - 2. * mid) + 0.5;
        }
    }
    double invers(const double val)
    {
        if(val < 0.5) {
            return 2. * (mid - min) * val + min;
        } else {
            return 2. * (max - mid) * val + mid - (max - mid);
        }
    }
};
}
#endif
