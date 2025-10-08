#include "chordmethod.h"

double ChordMethod::findRoot(double a, double b, double epsilon, int maxIter) {
    if (func(a) * func(b) >= 0) return NAN; // Invalid interval
    double c = a;
    for (int i = 0; i < maxIter; i++) {
        c = (a * func(b) - b * func(a)) / (func(b) - func(a));
        if (std::fabs(func(c)) < epsilon) break;
        if (func(c) * func(a) < 0) b = c;
        else a = c;
    }
    return c;
}
