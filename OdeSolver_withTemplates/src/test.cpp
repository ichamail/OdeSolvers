#include "test.h"
#include "OdeSolver.h"
#include "OdeFunction.h"

void test(){

    DampedHarmonicOscillator f;
    DoublePendulum g;

    ForwardEuler<DampedHarmonicOscillator> fweSolver{f};
    RungeKutta4<DoublePendulum> rk4Solver{g};

    // ForwardEuler fweSolver{f};   // template argument deduction from compiler
    // RungeKutta4 rk4Solver{g};    // template argument deduction from compiler

}

