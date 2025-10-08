#ifndef CHORDMETHOD_H
#define CHORDMETHOD_H

#include <cmath>

class ChordMethod {
public:
    double findRoot(double a, double b, double epsilon, int maxIter);
private:
    double func(double x) { return x*x*x - x*x + 2; } // Fixed function as example
};

#endif // CHORDMETHOD_H
