#ifndef _DICE_H_
#define _DICE_H_

#define MAXPROBABILITY 90

#include <stdlib.h>
#include <string>

using namespace std;

// The rool dice, probabillity is 0~100
int dice(int focus, int dicePool, int probability);

// probabillity is 0~100, return 0~100
double getExpectProbability(int focus, int diceNum, int expectNum, double probability);

// input 0~100, return "XX.X%"
string formatProbability(double probability);

//only for 0~10
int factorial(int n);

// n C k
int combination(int n, int k);

#endif // _DICE_H_