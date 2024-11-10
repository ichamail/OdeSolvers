#include "test.h"

#include "odeFunctions.h"
#include "OdeSolver.h"

void test(){

    vectorFunction f = dampedHarmonicOscillator;
    size_t numOfEquations{2};
    ForwardEuler fweSolver{numOfEquations, f};

    vectorFunction g = doublePendulum;
    numOfEquations = 4;
    RungeKutta4 rk4Solver{numOfEquations, g};

}
