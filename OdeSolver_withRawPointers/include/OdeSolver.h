#ifndef _ODESOLVER_H_
#define _ODESOLVER_H_

#include <cstddef> // to use size_t
#include <fstream>
typedef double (*scalarFunction)(double, double);
typedef double* (*vectorFunction)(double*, double);


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

    size_t numOfEquations;

    vectorFunction f;
    
    double** x;
    double* t;
    double* x0;

    size_t i;

    virtual double* advance() = 0; // pure virtual function

public:

    // constructor
    OdeSolver(size_t numOfEqs, vectorFunction Function);

    // copy constructor
    OdeSolver(const OdeSolver& object);

    // move constructor
    OdeSolver(OdeSolver &&object);

    // overloading copy assingnment
    OdeSolver& operator=(const OdeSolver &rhs);

    virtual ~OdeSolver();

    void setInitialConditions(double* arg_x0);

    void solve(double time[], size_t numOfTimeSteps);

    void printSolution();

    void writeSolution();

};


// concrete class
class ForwardEuler: public OdeSolver{

private:

    double* advance() override;

public:

    ForwardEuler(size_t numOfEqs, vectorFunction Function);

};


// concrete class
class RungeKutta4: public OdeSolver{

private:

    double* advance() override;
    
    double* step(double* k, double factor) ;

public:

    RungeKutta4(size_t numOfEqs, vectorFunction Function);

};


#endif
