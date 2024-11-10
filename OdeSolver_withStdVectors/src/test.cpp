#include "test.h"
#include "OdeSolver.h"
#include "OdeFunction.h"


void test(){
    
    DampedHarmonicOscillator f{};
    
    DoublePendulum g{};

    ForwardEuler fweSolver{&f};

    RungeKutta4 rk4Solver{&g};

}
