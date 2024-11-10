#ifndef _GET_INPUT_FROM_USER_H_
#define _GET_INPUT_FROM_USER_H_

#include "OdeSolver.h"

typedef unsigned long long size_t;
typedef double* (*vectorFunction)(double*, double);

void displayMainMenu();

void displaySolverMenu();

char getSelection();

void handleQuit();

void handleUnknown();

void handleDampedHarmonicOscillator();

void handleDoublePendulum();

void selectSolver(vectorFunction& f, size_t& numOfEquations);

void handleForwardEuler(vectorFunction& f, size_t& numOfEquations);

void handleRungeKutta(vectorFunction& f, size_t& numOfEquations);

void handleSolution(OdeSolver& solver, size_t& numOfEquations);

double getTimeStep();

size_t getNumOfTimeSteps();

double* getInitialConditions(size_t& numOfEquations);

#endif
