#include "OdeSolver.h"


/******************* abstract base class **********************/

// constructor
OdeSolver::OdeSolver(OdeFunction* function): ptr_f{function}, t{}, x{}, i{0} {
}

// copy constructor
OdeSolver::OdeSolver(const OdeSolver& object):OdeSolver{object.ptr_f} {}

// move constructor
OdeSolver::OdeSolver(OdeSolver &&object):OdeSolver{object.ptr_f} {
        object.ptr_f = nullptr;
    }

// overloading copy assingnment
OdeSolver& OdeSolver::operator=(const OdeSolver &rhs){
    if (this == &rhs){
        return *this;
    }

    ptr_f = rhs.ptr_f;

    return *this;
}

// destructor
OdeSolver::~OdeSolver(){
        ptr_f=nullptr;
    }

void OdeSolver::setInitialConditions(std::vector<double> x0){
        x.push_back(x0);
};

void OdeSolver::solve(std::vector<double> _t){
        
    t = _t;

    for (size_t j{0}; j<t.size()-1; ++j){
        i = j;
        x.push_back( advance() );
    }
}

void OdeSolver::printSolution(){

    for (size_t i{0}; i<t.size(); ++i){
        std::cout << "t" << i << " = " << t.at(i);
        for (size_t j{0}; j<x.at(i).size(); ++j){
            std::cout << ", x" << i << j << " = " << x.at(i).at(j);
        }
        std::cout << std::endl;
    }
}

void OdeSolver::writeSolution(){
    
    std::ofstream solutionFile;
    solutionFile.open("docs/solution_data.csv"); // "-O2" optimization create problems
    
    solutionFile << "t";
    for (size_t i{}; i<x.at(0).size(); ++i){
        solutionFile << "," << "x" << i ;
    }

    for (size_t i{}; i<t.size(); ++i){
        solutionFile << "\n" << t.at(i);
        for (size_t j{}; j<x.at(i).size(); ++j){
            solutionFile << "," << x.at(i).at(j);
        }
    }

    solutionFile.close();
}



/******************* concrete class ForwardEuler Method **********************/
ForwardEuler::ForwardEuler(OdeFunction* function)
    : OdeSolver(function) {
}

std::vector<double> ForwardEuler::advance() {

    OdeFunction& f = *ptr_f;
    
    double dt { t[i+1] - t[i] };

    std::vector<double> xDot = f(x[i], t[i]);

    std::vector<double> xNext(xDot.size());

    for (size_t j{0}; j<xDot.size(); ++j){
    xNext[j] = x[i][j] + dt * xDot[j];
    }

    return xNext;
}


/******************* concrete class Runge-Kutta Method **********************/

// constructor
RungeKutta4::RungeKutta4(OdeFunction* function)
    :OdeSolver(function){
}


std::vector<double> RungeKutta4::step(std::vector<double> k, double dt){
    
    OdeFunction& f = *ptr_f;

    std::vector<double> xStep(k.size());

    for (size_t j{0}; j<xStep.size(); ++j){
        xStep[j] = x[i][j] +  dt * k[j];
    }

    return f(xStep, t[i] + dt);
}


std::vector<double> RungeKutta4::advance() {

    OdeFunction& f = *ptr_f;

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
    




