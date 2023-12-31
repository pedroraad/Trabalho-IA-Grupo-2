#ifndef ALGORITHMS_H_INCLUDED
#define ALGORITHMS_H_INCLUDED

#include <iostream>
#include <vector>
#include <tuple>
#include <list>
#include <cmath>
#include <fstream>

using namespace std;

void breadthFirstSearch(int x, int y, int order);
void depthFirstSearch(int x, int y, int order);
void greedySearch(int x, int y, int order);
void backtracking(int x, int y, int order);
void orderedSearch(int x, int y, int order);
void aStarSearch(int x, int y, int order);

#endif