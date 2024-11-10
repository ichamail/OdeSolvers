#include "ODESolver.h"
#include <stdexcept>
#include <iostream>


// methods of abstract base class

// costructor
OdeSolver::OdeSolver(size_t numOfEqs, vectorFunction Function): numOfEquations{numOfEqs}, f{Function}, x{nullptr}, t{nullptr}, x0{nullptr}, i{0} {

    x0 = new double[numOfEquations];
    for (size_t j {0}; j<numOfEquations; ++j){
        x0[j] = 0.0;
    }
    
}

// copy constructor
OdeSolver::OdeSolver(const OdeSolver& object)
    :OdeSolver{object.numOfEquations, object.f} {

}

// move constructor
OdeSolver::OdeSolver(OdeSolver &&object)
    :OdeSolver{object.numOfEquations, object.f} {
    
    object.f = nullptr;
}

// overloading copy assignment
OdeSolver& OdeSolver::operator=(const OdeSolver &rhs){
    if (this == &rhs){
        return *this;
    }

    numOfEquations = rhs.numOfEquations;
    f = rhs.f;
    return *this;
}


// destructor
OdeSolver::~OdeSolver()
{
    f = nullptr;
    

    for (size_t j{0}; j<i; ++j){
        delete [] x[j];
    }
    delete[] x;
    delete[] t;
}


void OdeSolver::setInitialConditions(double* arg_x0){
    for (size_t j{0}; j<numOfEquations; ++j){
        x0[j]=arg_x0[j];
    }
}

void OdeSolver::solve(double time[], size_t numOfTimeSteps){

    t = time;

    x = new double*[numOfTimeSteps];
    x[0] = x0;

    for (size_t j{0}; j<numOfTimeSteps-1; ++j){
        i = j;
        x[i+1] = advance();
    }

    i = numOfTimeSteps;  // helping the destructor

}

void OdeSolver::printSolution(){

    for (size_t j{0}; j<i; ++j){
        std::cout << "t" << j << " = " << t[j];
        for (size_t k{0}; k<numOfEquations; ++k){
            std::cout << ", x" << j << k << " = " << x[j][k];
        }
        std::cout << std::endl;
    }

}

void OdeSolver::writeSolution(){
    std::ofstream solutionFile;
    solutionFile.open("docs/solution_data.csv"); // "-O2" optimization create problems
    
    solutionFile << "t";
    for (size_t j{}; j<numOfEquations; ++j){
        solutionFile << "," << "x" << j ;
    }

    for (size_t j{}; j<i; ++j){
        solutionFile << "\n" << t[j];
        for (size_t k{}; k<numOfEquations; ++k){
            solutionFile << "," << x[j][k];
        }
    }

    solutionFile.close();
}



// methods of concrete classes

/*******************Forward Euler Method*******************/
// costructor
ForwardEuler::ForwardEuler(size_t numOfEqs, vectorFunction Function)
    :OdeSolver(numOfEqs, Function){

}

double* ForwardEuler::advance() {
    double dt { t[i+1] - t[i] };

    double* fVec {nullptr};
    fVec = f(x[i], t[i]);

    double* xVec_next {nullptr};
    xVec_next = new double[numOfEquations];

    for (size_t j{0}; j<numOfEquations; ++j){
        xVec_next[j] = x[i][j] + dt * fVec[j];
    }

    return xVec_next;
}


/*******************Runge Kutta 4*******************/
// costructor
RungeKutta4::RungeKutta4(size_t numOfEqs, vectorFunction Function)
    :OdeSolver(numOfEqs, Function){

}

double* RungeKutta4::advance() {

    double dt {t[i+1] - t[i]};
    
    //Runge Kutta Step 1
    double* k1 {nullptr};
    k1 = f(x[i], t[i]);

    //Runge Kutta Step 2
    double* k2 {nullptr};
    k2 = step(k1, dt/2);
    
    //Runge Kutta Step 3
    double* k3 {nullptr};
    k3 = step(k2, dt/2);

    //Runge Kutta Step 4
    double* k4 {nullptr};
    k4 = step(k3, dt);


    double* xVec_next {nullptr};
    xVec_next = new double[numOfEquations];

    for (size_t j{0}; j<numOfEquations; ++j){
        xVec_next[j] = x[i][j] + dt/6 * (k1[j] + 2*k2[j] + 2*k3[j] + k4[j]);
    }

    delete[] k1; delete[] k2; delete[] k3; delete[] k4;


    return xVec_next;
}
    
double* RungeKutta4::step(double* k, double dt){
    
    double* xVec {nullptr};
    xVec = new double[numOfEquations];

    for (size_t j{0}; j<numOfEquations; ++j){
        xVec[j] = x[i][j] +  dt * k[j];
    }

    return f(xVec, t[i] + dt);
}
