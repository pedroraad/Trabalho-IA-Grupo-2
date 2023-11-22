#include <iostream>
#include "Performance.h"

using namespace std;

Performance::Performance()
{
}

void Performance::start()
{
    this->startTime = clock();
}

void Performance::end()
{
    this->finalTime = clock();

    printResult();
}

void Performance::printResult()
{

    cout << "Tempo de execução: " << (finalTime - startTime) / ((float)CLOCKS_PER_SEC) << " Segundos" << endl;
}

Performance::~Performance()
{
}