#include <iostream>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <fstream>
#include <list>

extern "C" {
    #include "picosat.h"
}

// Global variables - used in the functions called her.
char *solution = 0;
int nofVars;
PicoSAT *picosat;

void printSolution() {
    std::cout << solution << "\n";
    std::cout.flush();
}

void ruleOutCurrentSolutionAndDominatedPoints() {
    for (int i=0;i<nofVars;i++) {
        if (solution[i] == '1') picosat_add(picosat,-1*i-1);
    }
    picosat_add(picosat,0);
}

void ruleOutCurrentSolutionAndDominatingPoints() {
    for (int i=0;i<nofVars;i++) {
        if (solution[i] == '0') picosat_add(picosat,i+1);
    }
    picosat_add(picosat,0);
}

bool computeNextParetoPoint() {

    picosat_push(picosat);

    int result = picosat_sat(picosat,-1);
    if (result==PICOSAT_UNSATISFIABLE) return false;
    else if (result!=PICOSAT_SATISFIABLE) {
        throw "Internal error (3)";
    }

    while (true) {
        // Try to maximize the number of values
        for (int i=0;i<nofVars;i++) {
            int val = picosat_deref(picosat,i+1);
            if (val==-1) solution[i] = '0';
            else solution[i] = '1';
        }

        // One more...
        for (int i=0;i<nofVars;i++) {
            if (solution[i] == '0') picosat_add(picosat,i+1);
        }
        picosat_add(picosat,0);

        for (int i=0;i<nofVars;i++) {
            if (solution[i] == '1') picosat_assume(picosat,i+1);
        }

        result = picosat_sat(picosat,-1);

        if (result==PICOSAT_UNSATISFIABLE) {
            picosat_pop(picosat);
            return true;
        } else if (result!=PICOSAT_SATISFIABLE) {
            throw "Internal error (2)";
        }
   }
}

int main(int nofArgs, char **args) {

    std::string inputFile = "";
    for (int i=1;i<nofArgs;i++) {
        inputFile = args[i];
    }

    // Source of the following lines: https://stackoverflow.com/questions/10150468/how-to-redirect-cin-and-cout-to-files
    std::ifstream in(inputFile);
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    (void)cinbuf;
    if (inputFile!="") {
        std::cin.rdbuf(in.rdbuf()); // reading input file.
    }


    picosat = picosat_init();

    try {
        // READ INIT LINE
        std::string initLine;
        std::getline(std::cin,initLine);
        {
            std::istringstream is(initLine);
            std::string dat;
            is >> dat;
            if (is.fail()) throw "Error reading init line (1)";
            if (dat!="INIT") throw "Error reading init line (2)";
            is >> nofVars;
            if (is.fail()) throw "Error reading init line (3)";
        }

        solution = new char[nofVars+1];
        solution[nofVars] = 0;
        for (int i=0;i<nofVars;i++) picosat_inc_max_var (picosat);


        // Read constraint lines
        while (true) {
            std::string cLine;
            std::getline(std::cin,cLine);
            cLine.erase(cLine.find_last_not_of("\n\t ") + 1);
            if (cLine=="START") break;

            // Clause
            std::istringstream clauseLine(cLine);
            do {
                int a;
                clauseLine >> a;
                if (clauseLine.fail()) {
                    throw "Parsing number error";
                } else {
                    picosat_add(picosat,a);
                }
                if (clauseLine.eof()) {
                    picosat_add(picosat,0);
                    break;
                }
            } while (true);
        }

        if (!computeNextParetoPoint()) {
            std::cout << "SOLUTIONS:\nEND\n";
            return 0;
        }
        printSolution();

        std::list<std::string> paretoOptima;

        while (true) {

            // What about this point? Is it good?
            std::string thisLine;
            std::getline(std::cin,thisLine);
            if (thisLine=="Y") {
                // Optimize the current solution to a Pareto point
                // std::cerr << "READ: '" << thisLine << "'\n";
                // Use assume to avoid push's and pops
                for (int i=0;i<nofVars;i++) {
                    if (solution[i]=='1') {
                        solution[i] = '0';

                        for (int j=0;j<nofVars;j++) {
                            if (solution[j]=='1') {
                                picosat_assume(picosat,j+1);
                            } else if (solution[j]=='0') {
                                picosat_assume(picosat,-1*j-1);
                            } else {
                                throw "Internal error (1)";
                            }
                        }

                        int result = picosat_sat(picosat,-1);

                        if (result==PICOSAT_UNSATISFIABLE) {
                            // Ok, can't take this one away...
                            solution[i] = '1';
                        } else if (result==PICOSAT_SATISFIABLE) {
                            // Ask the oracle
                            printSolution();
                            std::string thisLine;
                            std::getline(std::cin,thisLine);
                            // std::cerr << "READ: '" << thisLine << "'\n";
                            if (thisLine=="Y") {
                                // Is fine.
                            } else if (thisLine=="N") {
                                // Add negative clause
                                ruleOutCurrentSolutionAndDominatingPoints();
                                solution[i] = '1';
                            } else {
                                std::cerr << "Error: Illegal read line: '" << thisLine << "'\n";
                                return 1;
                            }
                        } else {
                            throw "Illegal Picosat result.";
                        }
                    }
                }

                // Ok, new Pareto point found!
                paretoOptima.push_back(solution);
                ruleOutCurrentSolutionAndDominatedPoints();

            } else if (thisLine=="N") {
                // Not good. Remove
                ruleOutCurrentSolutionAndDominatingPoints();
            } else {
                std::cerr << "Error: Illegal read line: '" << thisLine << "'\n";
                return 1;
            }

            if (!computeNextParetoPoint()) {
                std::cout << "SOLUTIONS:\n";
                for (auto &b : paretoOptima) {
                    std::cout << b << "\n";
                }
                std::cout << "END\n";
                return 0;
            }
            printSolution();
        };



    } catch (const char *c) {
        std::cerr << c;
        if (solution!=0) delete[] solution;
        picosat_reset(picosat);
        return 1;
    }
    if (solution!=0) delete[] solution;
    picosat_reset(picosat);
    return 0;
}
