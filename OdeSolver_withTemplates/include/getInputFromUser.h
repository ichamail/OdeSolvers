#ifndef _GET_INPUT_FROM_USER_H_
#define _GET_INPUT_FROM_USER_H_

#include <vector>
#include "OdeSolver.h"
#include "OdeFunction.h"

typedef unsigned long long size_t;

void displayMainMenu();

void displaySolverMenu();

char getSelection();

void handleQuit();

void handleUnknown();

void handleDampedHarmonicOscillator();

void handleDoublePendulum();


double getTimeStep();

size_t getNumOfTimeSteps();

std::vector<double> getInitialConditions(size_t& numOfEquations);


template<class OdeFuntionType>
void selectSolver(OdeFuntionType& f, size_t& numOfEquations){

    char selection {};

    do {
        
        displaySolverMenu(); 

        selection = getSelection();

        switch (selection)
        {
        case 'E':
            handleForwardEuler(f, numOfEquations);
            break;
        
        case 'R':
            handleRungeKutta(f, numOfEquations);
            break;
        
        case 'Q':
            
            break;

        default:
            handleUnknown();

        }

    } while (selection !='Q');

}

template<class OdeFuntionType>
void handleForwardEuler(OdeFuntionType& f, size_t& numOfEquations){

    ForwardEuler<OdeFuntionType> solver{f};

    handleSolution(solver, numOfEquations);

}

template<class OdeFuntionType>
void handleRungeKutta(OdeFuntionType& f, size_t& numOfEquations){

    RungeKutta4<OdeFuntionType> solver{f};

    handleSolution(solver, numOfEquations);
}

template<class OdeSolverType>
void handleSolution(OdeSolverType& solver, size_t& numOfEquations){

    std::cout << "\nSolution Parameters:" << std::endl;
    std::cout << "------------------------------------------------" <<std::endl;

    solver.setInitialConditions(getInitialConditions(numOfEquations));

    double timeStep = getTimeStep();
    size_t numOfTimeSteps = getNumOfTimeSteps();
    
    std::vector<double> t(numOfTimeSteps);
    for (size_t i{}; i<numOfTimeSteps-1; ++i){
        t[i+1] = t[i]+timeStep;
    }

    solver.solve(t);

    solver.printSolution();
    solver.writeSolution();

}



#endif
