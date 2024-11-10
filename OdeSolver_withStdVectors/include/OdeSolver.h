#ifndef _ODE_SOLVER_H_
#define _ODE_SOLVER_H_

#include <cstddef> // to use size_t
#include <vector>
#include <iostream>
#include <fstream>
#include "OdeFunction.h"

/************ ODE SOLVER *******************************************
 * 
 *  ordinary differential equation:
 *  x' = f(x(t),t) , x(t0)=x0
 * 
 *  systmem of ordinary differential equations: 
 *  X' = f(X(t), t), X(t0) = X0
 * 
 *  [ x0'           [ x0                 [ x0(t0)          [ x00
 *    x1'             x1                   x1(t0)            x10
 *    x2'      = f(   x2     , t)  ,       x2(t0)      =     x20
 *    ...             ...                   ...               ...
 *    xn-1' ]         xn-1 ]               xn-1(t0) ]        xn-1,0 ]
 * 
 *******************************************************************/

// abstract base class
class OdeSolver{

protected:

    OdeFunction* ptr_f;
       
    std::vector<double> t;
    std::vector<std::vector<double>> x;
    size_t i;

    virtual std::vector<double> advance()=0; // pure virtual function

public:

    // constructor
    OdeSolver(OdeFunction* function);

    // copy constructor
    OdeSolver(const OdeSolver& object);

    // move constructor
    OdeSolver(OdeSolver &&object);

    // overloading copy assingnment
    OdeSolver& operator=(const OdeSolver &rhs);

    virtual ~OdeSolver();


    void setInitialConditions(std::vector<double> x0);

    void solve(std::vector<double> _t);

    void printSolution();

    void writeSolution();

};


// concrete class
class ForwardEuler: public OdeSolver {
    
private:

    std::vector<double> advance() override;

public:

    ForwardEuler(OdeFunction* function);

};


// concrete class
class RungeKutta4: public OdeSolver {

private:

    std::vector<double> step(std::vector<double> k, double dt);

    std::vector<double> advance() override;
    
    
public:

    RungeKutta4(OdeFunction* function);

};


#endif
