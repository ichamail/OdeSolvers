#include <iostream>
#include "getInputFromUser.h"

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

    std::cout << "\nDamped Harmonic Oscillator Parameters:" << std::endl;

    double m{};
    std::cout << "point mass m = ";
    std::cin >> m;
    std::cout << std::endl;

    double k{};
    std::cout << "spring constant k = ";
    std::cin >> k;
    std::cout << std::endl;

    double c{};
    std::cout << "damping coefficient c = ";
    std::cin >> c;
    std::cout << std::endl;

    DampedHarmonicOscillator f{m, k, c};

    selectSolver(f, numOfEquations);
    
}

void handleDoublePendulum(){
    
    size_t numOfEquations = 4;
    
    std::cout << "\nDouble Rod Pendulum Parameters:" << std::endl;

    double m1{};
    std::cout << "point mass m1 = ";
    std::cin >> m1;
    std::cout << std::endl;

    double m2{};
    std::cout << "point mass m2 = ";
    std::cin >> m2;
    std::cout << std::endl;


    double l1{};
    std::cout << "rod length l1 = ";
    std::cin >> l1;
    std::cout << std::endl;


    double l2{};
    std::cout << "rod length l2 = ";
    std::cin >> l2;
    std::cout << std::endl;

    double g{};
    std::cout << "gravitational acceleration g = ";
    std::cin >> g;
    std::cout << std::endl;

    DoublePendulum f {m1, m2, l1, l2, g};

    selectSolver(f, numOfEquations);

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

std::vector<double> getInitialConditions(size_t& numOfEquations){

    std::vector<double> x0(numOfEquations);
    
    for (size_t i{0}; i<numOfEquations; ++i){
        std::cout << "give initial condition x" << i << "(t0) = ";
        std::cin >> x0[i];
        std::cout << std::endl;
    }

    return x0;

}
