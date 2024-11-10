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

void selectSolver(OdeFunction& f, size_t& numOfEquations);

void handleForwardEuler(OdeFunction& f, size_t& numOfEquations);

void handleRungeKutta(OdeFunction& f, size_t& numOfEquations);

void handleSolution(OdeSolver& solver, size_t& numOfEquations);

double getTimeStep();

size_t getNumOfTimeSteps();

std::vector<double> getInitialConditions(size_t& numOfEquations);

#endif
