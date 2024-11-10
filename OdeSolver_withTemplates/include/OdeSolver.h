#ifndef _ODE_SOLVER_H_
#define _ODE_SOLVER_H_

#include <cstddef> // to use size_t
#include <vector>
#include <iostream>
#include <fstream>

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
template<typename OdeFunctionType>
class OdeSolver{
    
protected:

    OdeFunctionType f;
    
    std::vector<double> t;
    std::vector<std::vector<double>> x;
    size_t i;

    virtual std::vector<double> advance()=0; // pure virtual function

public:

    // constructor
    OdeSolver(OdeFunctionType function): f{function}, t{}, x{}, i{0} {}

    // copy constructor
    OdeSolver(const OdeSolver& object):OdeSolver{object.f} {}

    // move constructor
    OdeSolver(OdeSolver &&object):OdeSolver{object.f} {}

    // overloading copy assingnment
    OdeSolver& operator=(const OdeSolver &rhs){
        if (this == &rhs){
            return *this;
        }

        f = rhs.f;
        return *this;
    }

    virtual ~OdeSolver()=default;

    void setInitialConditions(std::vector<double> x0){
        x.push_back(x0);
    };


    void solve(std::vector<double> _t){
        
        t = _t;

        for (size_t j{0}; j<t.size()-1; ++j){
            i = j;
            x.push_back( advance() );
        }
    }

    void printSolution(){

        for (size_t i{0}; i<t.size(); ++i){
            std::cout << "t" << i << " = " << t.at(i);
            for (size_t j{0}; j<x.at(i).size(); ++j){
                std::cout << ", x" << i << j << " = " << x.at(i).at(j);
            }
            std::cout << std::endl;
        }
    }

    void writeSolution(){
        
        std::ofstream solutionFile;  // "-O2" optimization creates problems
        solutionFile.open("docs/solution_data.csv");

        solutionFile << 't';
        for (size_t i{}; i<x.at(0).size(); ++i){
            solutionFile << ',' << 't' << i ;
        }

        for (size_t i{}; i<t.size(); ++i){
            solutionFile << '\n' << t.at(i);
            for (size_t j{}; j<x.at(i).size(); ++j){
                solutionFile << ',' << x.at(i).at(j);
            }
        }

        solutionFile.close();
    }

};


// concrete class
template<typename OdeFunctionType>
class ForwardEuler: public OdeSolver<OdeFunctionType> {

    // for accessing `f`, `x`, `t` and `i` directly without `this->`
    using OdeSolver<OdeFunctionType>::f; 
    using OdeSolver<OdeFunctionType>::x;
    using OdeSolver<OdeFunctionType>::t;
    using OdeSolver<OdeFunctionType>::i;

private:

    std::vector<double> advance() override {
        
        double dt { t[i+1] - t[i] };

        std::vector<double> xDot = f(x[i], t[i]);

        std::vector<double> xNext(xDot.size());

        for (size_t j{0}; j<xDot.size(); ++j){
        xNext[j] = x[i][j] + dt * xDot[j];
        }

        return xNext;
    }

public:

    ForwardEuler(OdeFunctionType function)
        : OdeSolver<OdeFunctionType>(function) {
    }

};


// concrete class
template<typename OdeFunctionType>
class RungeKutta4: public OdeSolver<OdeFunctionType> {

    // for accessing `f`, `x`, `t` and `i` directly without `this->`
    using OdeSolver<OdeFunctionType>::f; 
    using OdeSolver<OdeFunctionType>::x;
    using OdeSolver<OdeFunctionType>::t;
    using OdeSolver<OdeFunctionType>::i;

private:

    std::vector<double> step(std::vector<double> k, double dt){
    
        std::vector<double> xStep(k.size());

        for (size_t j{0}; j<xStep.size(); ++j){
            xStep[j] = x[i][j] +  dt * k[j];
        }

        return f(xStep, t[i] + dt);
    }

    std::vector<double> advance() override{

        double dt {t[i+1] - t[i]};
        
        //Runge Kutta Step 1
        std::vector<double> k1 { f(x[i], t[i]) };

        //Runge Kutta Step 2
        std::vector<double> k2 { step(k1, dt/2) };
        
        //Runge Kutta Step 3
        std::vector<double> k3 { step(k2, dt/2) };

        //Runge Kutta Step 4
        std::vector<double> k4 { step(k3, dt) };


        std::vector<double> xNext(k1.size());

        for (size_t j{0}; j<xNext.size(); ++j){
            xNext[j] = x[i][j] + dt/6 * (k1[j] + 2*k2[j] + 2*k3[j] + k4[j]);
        }

        return xNext;
    }
    
    
public:

    RungeKutta4(OdeFunctionType function)
        :OdeSolver<OdeFunctionType>(function){
    }

};


#endif
