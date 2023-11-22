#ifndef PERFORMANCE_H_INCLUDED
#define PERFORMANCE_H_INCLUDED
#include <chrono>
#include <ctime>
#include <cstdint>

using namespace std;

class Performance
{

private:
    clock_t startTime, finalTime;
    void printResult();

public:
    Performance();
    ~Performance();

    void start();
    void end();
};

#endif