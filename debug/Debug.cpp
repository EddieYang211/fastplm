#include <fstream>
#include <iostream>

#include "MatrixReader.h"
#include "GPSolver.h"

using namespace std;

void MAP(ifstream &input) {
    int paramCount, timeCount, indivCount;
    input >> paramCount >> timeCount >> indivCount;
    
    auto Y = readMatrix(timeCount, indivCount, input, false);
    arma::cube X(timeCount, indivCount, paramCount);
    for (int i = 0; i < paramCount; i ++)
        X.slice(i) = readMatrix(timeCount, indivCount, input, false);
    std::cout << Y << "\n";
    
    int toisDim, iotsDim;
    input >> toisDim;
    auto toisCoeff = readMatrix(timeCount, toisDim, input, false);
    input >> iotsDim;
    auto iotsCoeff = readMatrix(indivCount, iotsDim, input, false);
    
    GPSolver solver(X, Y, toisCoeff, iotsCoeff, false);
    cout << solver.compute() << endl;
}

int main () {
    auto inputFile = "/Users/selveskii/Desktop/data.txt";
    ifstream input(inputFile);
    
    MAP(input);
    
    return 0;
}
