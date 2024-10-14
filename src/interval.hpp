#ifndef INTERVAL_H_
#define INTERVAL_H_

#include "util.hpp"

class Interval {
  public:
    double min, max;

    Interval() : min(inf), max(-inf) {};
    Interval(double min, double max) : min(min), max(max) {}

    double size() const { return max - min; }

    bool contains(double x) const { return min <= x && x <= max; }

    bool surrounds(double x) const { return min < x && x < max; }

    static const Interval empty, universe;
};

const Interval Interval::empty    = {inf, -inf};
const Interval Interval::universe = {-inf, inf};

#endif // INTERVAL_H_
