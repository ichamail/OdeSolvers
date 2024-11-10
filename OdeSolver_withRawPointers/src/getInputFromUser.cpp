#include <iostream>
#include "getInputFromUser.h"
#include "OdeSolver.h"
#include "odeFunctions.h"

void displayMainMenu(){
    
    std::cout << "\nList of Oridanary Differential Equations" << std::endl;
    std::cout << "------------------------------------------------" <<std::endl;

    std::cout << "A - Damped Harmonic Oscillator" << std::endl;
    std::cout << "B - Double Pendulum" << std::endl;
    std::cout << "Q - Exit Program" << std::endl;
    std::cout << "Enter your choice: ";
}

void displaySolverMenu(){

    std::cout << "\nList of Solvers" << std::endl;
    std::cout << "------------------------------------------------" <<std::endl;

    std::cout << "E - Forward Euler" << std::endl;
    std::cout << "R - Runge Kutta 4" << std::endl;
    std::cout << "Q - Return to Main Menu" << std::endl;
    std::cout << "Enter your choice: ";

}

char getSelection(){
    char selection {};
    std::cin >> selection;
    return toupper(selection);

}

void handleUnknown(){
    std::cout << "Unknown Selection. Try Again!" << std::endl;
}

void handleQuit(){
    std::cout << "Goodbye!\n" << std::endl;
}

void handleDampedHarmonicOscillator(){

    size_t numOfEquations = 2;

    vectorFunction f = dampedHarmonicOscillator;
    
    selectSolver(f, numOfEquations);
    
}

void handleDoublePendulum(){
    
    size_t numOfEquations = 4;

    vectorFunction f = doublePendulum;

    selectSolver(f, numOfEquations);

}

void selectSolver(vectorFunction& f, size_t& numOfEquations){

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

void handleForwardEuler(vectorFunction& f, size_t& numOfEquations){

    ForwardEuler solver{numOfEquations, f};

    handleSolution(solver, numOfEquations);

}

void handleRungeKutta(vectorFunction& f, size_t& numOfEquations){

    RungeKutta4 solver{numOfEquations, f};

    handleSolution(solver, numOfEquations);
}

void handleSolution(OdeSolver& solver, size_t& numOfEquations){

    std::cout << "\nSolution Parameters:" << std::endl;
    std::cout << "------------------------------------------------" <<std::endl;

    solver.setInitialConditions(getInitialConditions(numOfEquations));

    double dt = getTimeStep();
    size_t numOfTimeSteps = getNumOfTimeSteps();

    double *t {nullptr};
    t = new double [numOfTimeSteps]{0};
    for (size_t i{0}; i<numOfTimeSteps -1; ++i){
        t[i+1] = t[i] + dt;
    }

    solver.solve(t, numOfTimeSteps);

    solver.printSolution();
    solver.writeSolution();

}

double getTimeStep(){

    std::cout << "give time step dt = ";
    double dt {};
    std::cin >> dt;
    std:: cout << std::endl;

    return dt;

}

size_t getNumOfTimeSteps(){

    std::cout << "give number of time steps n = ";
    size_t numOfTimeSteps {};
    std::cin >> numOfTimeSteps;
    std:: cout << std::endl;

    return numOfTimeSteps;

}

double* getInitialConditions(size_t& numOfEquations){

    double* x0 {nullptr};
    x0 = new double[numOfEquations];
    for (size_t i{0}; i<numOfEquations; ++i){
        std::cout << "give initial condition x" << i << "(t0) = ";
        std::cin >> x0[i];
        std::cout << std::endl;
    }

    return x0;

}

