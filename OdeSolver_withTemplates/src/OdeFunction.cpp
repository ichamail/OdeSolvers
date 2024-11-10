#include "OdeFunction.h"


DampedHarmonicOscillator::DampedHarmonicOscillator(double m, double k, double c)
    : pointMass{m}, springConst{k}, dampingCoeff{c} {
}

DampedHarmonicOscillator::DampedHarmonicOscillator()
    : DampedHarmonicOscillator{default_m, default_k, default_c} {
}

DampedHarmonicOscillator::DampedHarmonicOscillator(double m)
    : DampedHarmonicOscillator{m, default_k, default_c} {
}

DampedHarmonicOscillator::DampedHarmonicOscillator(double m, double k)
    : DampedHarmonicOscillator{m, k, default_c} {
}

std::vector<double> DampedHarmonicOscillator::operator() (std::vector<double> x, double t) const {

    ++t; // unused variable

    std::vector<double> xDot(2);

    xDot.at(0) = x.at(1);

    xDot.at(1) = (
        - dampingCoeff/pointMass * x.at(1) - springConst/pointMass * x.at(0)
    );

    return xDot;
}
